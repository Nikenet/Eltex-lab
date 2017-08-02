// Warcraft. Заданное количество юнитов добывают золото равными
// порциями из одной шахты, задерживаясь в пути на случайное время,
// до ее истощения. Работа каждого юнита реализуется в 
// порожденном процессе.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int gold =500, fd[2];
	char buf[80], str[20];

	while (gold > 0){
		
		pipe(fd);
		pid = fork();

		if(-1 == pid){
			perror("fork");
			exit(1);
		}

		if (pid == 0){
			srand (getpid());
			int random = rand() % 2+1;
			sleep(random);
			sprintf(str, "Gold is: %d\n", gold);
			close(fd[0]);		
			write(fd[1], str, (strlen(str)+1));			
			exit(0);
		}

		if (pid > 0){
			wait(NULL);
			gold = gold -15;
			close(fd[1]);
			read(fd[0], buf, sizeof(buf));
			printf("Received string: %s", buf);
		}
	}	
}

