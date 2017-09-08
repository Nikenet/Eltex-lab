#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>

#define RCVBUFSIZE 10	/* Size of receive buffer */
#define MSGSZ      10	/* Size of text in MSG*/
#define KEY        10	/* Key for msgget*/

typedef struct msgbuf {
	long    mtype;
	char    mtext[MSGSZ];
} message_buf;

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
	char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
	int recvMsgSize;                    /* Size of received message */
	int msqid;							/* MSG descriptor */
	int msgflg = IPC_CREAT | 0666;		/* MSG flags */
	key_t key = KEY;					/* Key for MSG */
	message_buf sbuf;					/* Struct to MSG*/
	size_t buf_length;					/* Size of message in MSG*/


	if ((msqid = msgget(key, msgflg )) < 0){
		perror("msgget");
		exit(1);
	} else
		printf("Msgget:\tmsgget succeeded:\tmsqid = %d\n", msqid);

	sbuf.mtype = 1;

	if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
		DieWithError("recv() failed");

	while (recvMsgSize > 0)		/* zero indicates end of transmission */
	{
		strcpy(sbuf.mtext, echoBuffer);
		buf_length = sizeof(struct msgbuf) - sizeof(long);

		if (msgsnd(msqid, &sbuf, buf_length, 0) < 0) {
			printf ("%d, %ld, %s, %ld\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
			perror("msgsnd");
			exit(1);
		} else
			printf("Write to MSG:\t%s\t size\t%ld\n", sbuf.mtext, sizeof(sbuf.mtext));

		if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
			DieWithError("recv() failed");		
	}
	close(clntSocket);
}
