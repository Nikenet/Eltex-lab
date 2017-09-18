#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdint.h>
#include "message.pb-c.h" /* ProtoBuf generated header*/

#define MSGSZ 10	/* Size of text in MSG*/
#define KEY   15	/* Key for msgget*/

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

	void *buf;
	unsigned len;

	recvMsgSize = sizeof(struct msgbuf) - sizeof(long);	

	if ((msqid = msgget(key, 0666 )) < 0) {
		perror("msgget");
		exit(1);
	}	
	
	if (msgrcv(msqid, &rbuf, recvMsgSize, 1, 0) < 0) {
		perror("msgrcv");
	}        

	DMessage msg = DMESSAGE__INIT;   // DMESSAGE
	Submessage sub1 = SUBMESSAGE__INIT; // SUBMESSAGE A

	sub1.value = rbuf.mtext;
	msg.a = &sub1;       			        // Point msg.a to sub1 data 

	len = dmessage__get_packed_size (&msg); // This is the calculated packing length
	buf = malloc (len);                     // Allocate memory
	dmessage__pack (&msg, buf);             // Pack msg, including submessages

	if (send(clntSocket, buf, len, 0) != len)
		DieWithError("send() sent a different number of bytes than expected");

	printf("Read from MSG and send:\t%s\t%p\n", rbuf.mtext, buf);

	free(buf);
}
