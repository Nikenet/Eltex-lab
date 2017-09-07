#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>     /* for atoi() and exit() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 

#define RCVBUFSIZE 10   /* Size of receive buffer */
#define MAX_SEND_SIZE 10
#define FIFO1 "/tmp/fifo.1"
#define MAXLINE 80

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClientTwo(int clntSocket)
{
	char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
	int recvMsgSize;                    /* Size of received message */
	int readfd, writefd;
	char *str = (char *) malloc(sizeof(char) * 10);

	mkfifo(FIFO1, 0666);

	recvMsgSize = 10;
	
	/* Send received string and receive again until end of transmission */
	while (recvMsgSize > 0)      /* zero indicates end of transmission */
	{   
		close(readfd);  
		readfd = open(FIFO1, O_WRONLY, 0); // open and block pipe
        read(readfd, str, 10);      // read in pipe        

        printf("Read to FIFO: %s\n", str);

		/* Echo message back to client */
		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
			DieWithError("send() failed");

		
	}
	close(clntSocket);    /* Close client socket */
}
