#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <wait.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int gvx, gvy;

//структура для кординат
struct DATA{
	int x;
	int y;	
};
typedef struct DATA Data;

//функция, производящая вычисления
void *calc(void *arg){
	Data* a = (Data*)arg;
	a->x = a->x + gvx;
	a->y = a->y + gvy;
	pthread_exit(NULL);
}

int main(int argc, char const *argv[]){
	int count, shmid;	
	key_t key;
	int result;

	//вводим количество строк матрицы
	printf("Enter count of matrix\n");
	scanf("%d", &count);

	//вводим вектор, с которым будет происходить сложение
	printf("Enter x and y coordinate of vector\n");
	scanf("%d %d", &gvx, &gvy);	

	//создаем разделяемую память
	key = ftok(".", 'm');
	size_t shmsize = sizeof(struct DATA)*count;
	if ((shmid = shmget(key, shmsize, IPC_CREAT | 0666)) < 0) {
		perror("shmget error\n");
		exit(1);
	}

	//создаем указатель на начало разделяемой памяти
	Data *data = shmat (shmid, (void *) 0, 0);

	//заполяем структуру
	for (int i = 0; i < count; ++i){
		printf("Entex x and y\n");
		scanf("%d %d", &data[i].x, &data[i].y);	
	}

	//выводим содержимое разделяемой памяти
	printf("In shared memory now:\n");
	for (int i = 0; i < count; ++i)
	{
		printf("\t#%d  X: %d Y: %d\n",i, data[i].x, data[i].y);
	}

	//создаем потоки
	pthread_t threads[count];
	void *status[count];

	for (int i = 0; i < count; i++){
		result = pthread_create(&threads[i], NULL, calc, &data[i]);
		if (result != 0) {
			perror("Error reating the first thread");
			return EXIT_FAILURE;
		}
	}

	//ждем завершения потоков
	for (int i = 0; i < count; i++){
		result = pthread_join(threads[i], &status[i]);
		if (result != 0) {
			perror("Error joining the first thread");
			return EXIT_FAILURE;
		}
		free(status[i]);
	}

	//отключаемся от разделяемой памяти
	shmdt(data);

	return 0;
}
