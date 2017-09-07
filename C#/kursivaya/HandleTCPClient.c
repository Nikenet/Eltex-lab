#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>     /* for atoi() and exit() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RCVBUFSIZE 10   /* Size of receive buffer */
#define MAX_SEND_SIZE 10
#define FIFO1 "/tmp/fifo.1"
#define MAXLINE 80

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    int readfd, writefd;

    mkfifo(FIFO1, 0666); // create FIFO pipe

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {   
        close(writefd);
        writefd = open(FIFO1, O_WRONLY, 0); // open and block pipe
        write(writefd, echoBuffer, 10);    // write in pipe
        
        printf("Write to FIFO: %s\n", echoBuffer);

        /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");


    }

    close(clntSocket);    /* Close client socket */
}
