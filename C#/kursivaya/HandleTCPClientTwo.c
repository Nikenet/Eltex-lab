#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>     /* for atoi() and exit() */
#include <sys/types.h>
#include <sys/msg.h>

#define RCVBUFSIZE 10   /* Size of receive buffer */
#define MAX_SEND_SIZE 10
#define MSGSZ 10

typedef struct msgbuf {
	long    mtype;
	char    mtext[MSGSZ];
} message_buf;

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClientTwo(int clntSocket)
{
	int recvMsgSize;                    /* Size of received message */

	int msqid;
	key_t key;
	message_buf  rbuf;

	key = 10;

	if ((msqid = msgget(key, 0666 )) < 0) {
		perror("msgget");
		exit(1);
	}

	recvMsgSize = sizeof(struct msgbuf) - sizeof(long);
	
	/* Send received string and receive again until end of transmission */
			//look
		if (msgrcv(msqid, &rbuf, recvMsgSize, 1, 0) < 0) {
		perror("msgrcv");
		}        

		printf("Read to MSG: %s, size %ld\n", rbuf.mtext, sizeof(rbuf.mtext));

		/* Echo message back to client */
		if (send(clntSocket, rbuf.mtext, sizeof(rbuf.mtext), 0) != sizeof(rbuf.mtext))
			DieWithError("send() failed");
}

