#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MSGSZ 10	/* Size of text in MSG*/
#define KEY   10	/* Key for msgget*/

typedef struct msgbuf {
	long mtype;
	char mtext[MSGSZ];
} message_buf;

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPManages(int clntSocket)
{
	int recvMsgSize;       /* Size of received message */
	int msqid;             /* MSG descriptor */
	key_t key = KEY;       /* Key for MSG */
	message_buf rbuf;      /* Struct to MSG*/

	recvMsgSize = sizeof(struct msgbuf) - sizeof(long);	

	if ((msqid = msgget(key, 0666 )) < 0) {
		perror("msgget");
		exit(1);
	}	
	
	if (msgrcv(msqid, &rbuf, recvMsgSize, 1, 0) < 0) {
	perror("msgrcv");
	}        

	printf("Read to MSG:\t%s\t size\t%ld\n", rbuf.mtext, sizeof(rbuf.mtext));

	if (send(clntSocket, rbuf.mtext, sizeof(rbuf.mtext), 0) != sizeof(rbuf.mtext))
		DieWithError("send() failed");
}
