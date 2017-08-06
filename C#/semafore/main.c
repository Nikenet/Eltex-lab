#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv){

	int count;
	int *array;   /* Указатель на разделяемую память */
	pid_t pid;
	key_t key;
	int vx, vy;
	int shmid, semid;    /* IPC дескриптор для области разделяемой памяти и для семафора*/

	struct sembuf lock_res = {0, -1, 0};	//блокировка ресурса
	struct sembuf rel_res = {0, 1, 0};	//освобождение ресурса

	printf("Enter count of matrix\n");
	scanf("%d", &count);

	key = ftok(".", 'm');

	//создаем разделяемую память
	if ((shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(1);
	}

	//создаем семафор
	semid = semget(key, 1, 0666 | IPC_CREAT);
	semctl(semid, 0, SETVAL, 1);


	printf("Enter x and y coordinate of vector\n");
	scanf("%d %d", &vx, &vy);

	if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
		printf("Can't attach shared memory\n");
		exit(-1);
	}

	semop(semid, &lock_res, 1);

	for (int i = 0; i < count; ++i){
		printf("Enter x and y coordinate of matrix\n");
		scanf("%d %d", &array[i], &array[count*2-i]);
	}

	semop(semid, &rel_res, 1);

	for (int j = 0; j < count; ++j){
		pid = fork();

		if (pid == 0){
			semop(semid, &lock_res, 1);

			printf("CHILD #%d run\n", j);
			printf("CHILD #%d x %d y %d\n", j, array[j], array[count*2-j]);

			array[j] = array[j] + vx;
			array[count*2-j] = array[count*2-j] + vy;

			printf("CHILD #%d exit, result: x %d, y %d\n", j, array[j], array[count*2-j]);

			semop(semid, &rel_res, 1);
			
			exit(0);
		}
	}

	//ждем завершения всех процессов
	wait(NULL);

	//удалим созданную разделяемую память и семафор
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID);

	return 0;
}