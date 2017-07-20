// Винни-Пух и пчелы. Заданное количество пчел добывают мед равными порциями, 
// задерживаясь в пути на случайное время. Винни-Пух потребляет мед порциями 
// заданной величины за заданное время и столько же времени может прожить без
// питания. Работа каждой пчелы реализуется в порожденном процессе.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void vinney(int all_food, int vi_eat, int vi_delay){
	int t = all_food - vi_eat;
	sleep(vi_delay);
	return t;
}

void bee(){}

void parent(int pid, int status){
	printf("PARENT: Это процесс-родитель!\n");
	printf("PARENT: Мой PID -- %d\n", getpid());
	printf("PARENT: PID моего потомка %d\n",pid);
	printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
	if (wait(&status) == -1){
		perror("wait() error");
	} else if (WIFEXITED(status)){
		printf("PARENT: Код возврата потомка: %d\n", status/256);
		
	} else {
		perror("PARENT: потомок не завершился успешно");
	}
	printf("PARENT: Выход!\n");
}

void child(int pid, int status){
	printf(" CHILD: Это процесс-потомок!\n");
	printf(" CHILD: Мой PID -- %d\n", getpid());
	printf(" CHILD: PID моего родителя -- %d\n", getppid());
	printf(" CHILD: Введите мой код возврата (как можно меньше):");
	scanf("%d", &status);
	printf(" CHILD: Выход!\n");
	exit(status);
}
	
int main(int argc, char** argv) {

	int all_food, vi_eat, vi_delay;
	pid_t pid;
	int status;

	printf("Введите сколько и как часто Винни ест: \n");
	scanf("%d %d ", vi_eat, vi_delay);

	
	pid = fork();

	if (-1 == pid) {
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	} else if (0 == pid){
		child(pid, status);
	} else {
		parent(pid, status);
	}
}