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

int writefile(int ch){
	FILE *file;
	file = fopen("tmp.txt", "r+");
	fputc(ch, file);
	fclose(file);
	return 0;
}

int readfile(int ch){
	FILE *file;
	file = fopen("tmp.txt", "r");
	ch = fgetc(file);
	fclose(file);
	return ch;
}

int main(int argc, char** argv) {
	
	pid_t pid;
	int i, videlay, vieat,ch=64, food;
	
	writefile(ch);
	food = ch;

	printf("Vinne eats every:\n");
	scanf("%d", &videlay);
	printf("How many Vinne eats?:\n");
	scanf("%d", &vieat);

	for (i = 0; i < food; i++) {				
		pid = fork();			

		if (pid == -1) {
			printf("ERROR, pid == -1\n");
			return 0;
		}

		if (pid == 0) {

			if (i == 0){
				food = readfile(ch);
				while(food > 0){
					food = readfile(ch);
					ch = food - vieat;
					writefile(ch);
					printf("I'm Vinne and i'm eating, food is %d\n", food);
					sleep(videlay);

					if (food < vieat){
						printf("Vinne RIP\n");
						return 0;
					}										
				}				
			}
							
			srand (getpid());
			int random = rand() % 15+1;
			sleep(random);

			food = readfile(ch);
			ch = food +1;
			writefile(ch);

			if (food < vieat){
					printf("Vinne RIP\n");
					return 0;
				}

			printf("I'm bee, i'm sleeping %d, my number %d, food is %d\n", random, i, food);
			return 0;
			
		}
	}

	return 0;
}
