#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

int main()
{
	int *array;   /* Указатель на разделяемую память */
	int shmid;    /* IPC дескриптор для области разделяемой памяти */
	int new = 1;  /* Флаг необходимости инициализации элементов массива */
	int count = 5; //количество создаваемых потоков
	char pathname[] = "06-1a.c"; 
	key_t key;
	pid_t pid[count];
	int semid;
	
	union semun {
		int val;                  /* значение для SETVAL */
		struct semid_ds *buf;     /* буферы для  IPC_STAT, IPC_SET */
		unsigned short *array;    /* массивы для GETALL, SETALL */
		/* часть, особенная для Linux: */
		struct seminfo *__buf;    /* буфер для IPC_INFO */
	};

	union semun semstr;
	struct sembuf lock_res = {0, -1, 0};	//блокировка ресурса
	struct sembuf rel_res = {0, 1, 0};	//освобождение ресурса
	
	if((key = ftok(pathname,0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1);
	}
	
	if((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){	
		if(errno != EEXIST){			
			printf("Can\'t create shared memory\n");
			exit(-1);
		} else {			
			if((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
				printf("Can't find shared memory\n");
				exit(-1);
			}
			new = 0;
		}
	}

	//создаем семафор
	semid = semget(key, 1, 0666 | IPC_CREAT);
	semstr.val = 1;
	semctl(semid, 0, SETVAL, semstr);

	for (int i = 0; i < count; ++i){

		pid[i] = fork();

		if (pid[i] == 0){

			//waitpid(pid[i-1], 0, 0);
			
			/* Получим доступ к разделяемой памяти */
			if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
				printf("Can't attach shared memory\n");
				exit(-1);
			}
			
			//блокируем 
			semop(semid, &lock_res, 1);

			//производим операции
			if(new){
				array[0] = 0;
				array[1] = 1;
				array[2] = 1;
			} else {
				array[1] += 1;
				array[2] += 1;
			}

			printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n", array[0], array[1], array[2]);

			if(shmdt(array) < 0){ 
				printf("Can't detach shared memory\n");
				exit(-1);

			//разблокируем
			semop(semid, &rel_res, 1);

			//отключение от разделяемой памяти
			if (shmdt(array) < 0) {
				printf("Ошибка отключения\n");
				exit(1);
			}
			exit(0);
			}
		}
	}
	
	
	return 0;
}