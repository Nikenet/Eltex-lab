#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>     /* for atoi() and exit() */
#include <sys/types.h>
#include <sys/msg.h>


#define RCVBUFSIZE 10   /* Size of receive buffer */
#define MSGSZ     10

typedef struct msgbuf {
	long    mtype;
	char    mtext[MSGSZ];
} message_buf;


void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
	char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
	int recvMsgSize;                    /* Size of received message */
	int readfd, writefd;

	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	size_t buf_length;

	key = 10;

	if ((msqid = msgget(key, msgflg )) < 0) {
		perror("msgget");
		exit(1);
	}
	else 
		printf("msgget: msgget succeeded: msqid = %d\n", msqid);

	sbuf.mtype = 1;


	/* Receive message from client */
	if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
		DieWithError("recv() failed");

	/* Send received string and receive again until end of transmission */
	while (recvMsgSize > 0)      /* zero indicates end of transmission */
	{   

		strcpy(sbuf.mtext, echoBuffer);
		buf_length = sizeof(struct msgbuf) - sizeof(long);

		if (msgsnd(msqid, &sbuf, buf_length, 0) < 0) {
			printf ("%d, %ld, %s, %ld\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
			perror("msgsnd");
			exit(1);
		} 
		else
			printf("Write to MSG: %s\n", sbuf.mtext);

		/* See if there is more data to receive */
		if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
			DieWithError("recv() failed");

		
	}

	close(clntSocket);    /* Close client socket */
}
