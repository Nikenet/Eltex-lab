#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>

struct msgbuf {
	long mtype; /* тип сообщения, должен быть > О */ 
	int mtext[2]; /* данные */
	};

int main(int argc, char **argv){

	int msqid, count, vx, vy;
	
	struct msgbuf buf;
	pid_t pid;
	key_t key;

	printf("Enter x and y coordinate of vector\n");
	scanf("%d %d", &vx, &vy);

	printf("Enter count of matrix\n");
	scanf("%d", &count);

	key = ftok(".", 'm');
	msqid = msgget(key, 0600|IPC_CREAT);

	buf.mtype = 1;
	for (int i = 0; i < count; ++i){		
		
		printf("Enter x and y coordinate of matrix\n");
		scanf("%d %d", &buf.mtext[0], &buf.mtext[1]);
		msgsnd(msqid, &buf, sizeof(struct msgbuf) - sizeof(long), IPC_NOWAIT);
	}	
	
	for (int i = 0; i < count; ++i){

		pid = fork();

		if (pid == 0){

			int x, y;
			printf("CHILD #%d run\n", i);

			msgrcv(msqid, &buf, sizeof(struct msgbuf) - sizeof(long), buf.mtype, IPC_NOWAIT);				
			x = buf.mtext[0];
			y = buf.mtext[1];

			printf("CHILD #%d x %d y %d\n", i, x, y);

			x = x + vx;
			y = y + vy;
			
			printf("CHILD #%d exit, result: x %d, y %d\n", i, x, y);
			exit(0);
		}
	}

	wait(NULL);
	msgctl(msqid, IPC_RMID, NULL);

	return 0;
}