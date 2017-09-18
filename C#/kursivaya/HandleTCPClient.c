#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdint.h>
#include "message.pb-c.h"

#define RCVBUFSIZE 14	/* Size of receive buffer */
#define MSGSZ      14	/* Size of text in MSG*/
#define KEY        15	/* Key for msgget*/

typedef struct msgbuf {
	long    mtype;
	char  	mtext[MSGSZ];
} message_buf;

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{	
	DMessage   *msg;         // DMessage using submessages
  	Submessage *sub1;      // Submessages
  	
	int recvMsgSize;                    /* Size of received message */
	int msqid;							/* MSG descriptor */
	int msgflg = IPC_CREAT | 0666;		/* MSG flags */
	key_t key = KEY;					/* Key for MSG */
	message_buf sbuf;					/* Struct to MSG*/
	size_t buf_length;					/* Size of message in MSG*/
	uint8_t buf[MSGSZ];

	if ((msqid = msgget(key, msgflg )) < 0){
		perror("msgget");
		exit(1);
	} else
		printf("Msgget:\tmsgget succeeded:\tmsqid = %d\n", msqid);

	sbuf.mtype = 1;

	if ((recvMsgSize = recv(clntSocket, buf, RCVBUFSIZE, 0)) < 0)
		DieWithError("recv() failed");

	while (recvMsgSize > 0)		/* zero indicates end of transmission */
	{	
		msg = dmessage__unpack(NULL,RCVBUFSIZE,buf);
		if (msg == NULL) // Something failed
	    	fprintf(stderr,"error unpacking incoming message\n");	
		sub1 = msg->a;

		strcpy(sbuf.mtext, sub1->value);
		buf_length = sizeof(struct msgbuf) - sizeof(long);

		if (msgsnd(msqid, &sbuf, buf_length, 0) < 0) {
			printf ("%d, %ld, %s, %ld\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
			perror("msgsnd");
			exit(1);
		} else
			printf("Write to MSG:\t\t%s\n", sub1->value);

		if ((recvMsgSize = recv(clntSocket, buf, RCVBUFSIZE, 0)) < 0)
			DieWithError("recv() failed");

		dmessage__free_unpacked(msg,NULL);
	}
	close(clntSocket);
}
