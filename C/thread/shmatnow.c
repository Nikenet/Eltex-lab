#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

//структура для хранения данных
struct DATA{
	int x;
	int y;	
};
typedef struct DATA Data;

int main(int argc, char const *argv[])
{
	key_t key;
	int shmid, count;

	//вводим количество строк в матрице
	printf("Enter count of matrix\n");
	scanf("%d", &count);

	//генерируем ключ и пытаемся подключиться к уже существующей памяти
	key = ftok(".", 'm');
	size_t shmsize = sizeof(struct DATA)*count;
	if((shmid = shmget(key, shmsize, 0)) < 0){
		printf("Can\'t find shared memory\n");
		exit(-1);
	}!

	//позвращаем указатель на начало разделяемой памяти
	Data *data = shmat(shmid, (void *) 0, 0);

	//выводим содержимое
	printf("In shared memory now:\n");
	for (int i = 0; i < count; ++i){
		printf("\t#%d  X: %d Y: %d\n",i, data[i].x, data[i].y);
	}

	//удаляем разделяемую память
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}
