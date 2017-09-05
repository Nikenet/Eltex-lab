#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>     /* for atoi() and exit() */

#define RCVBUFSIZE 10   /* Size of receive buffer */
#define MAX_SEND_SIZE 10

void DieWithError(char *errorMessage);  /* Error handling function */

struct mymsgbuf {
        long mtype;
        char mtext[MAX_SEND_SIZE];
};

int msgqid, rc;

void send_message(int qid, struct mymsgbuf *qbuf, long type, char *text){
        qbuf->mtype = type;
        strcpy(qbuf->mtext, text);

        if((msgsnd(qid, (struct msgbuf *)qbuf,
                strlen(qbuf->mtext)+1, 0)) ==-1){
                perror("msgsnd");
                exit(1);
        }
}

void read_message(int qid, struct mymsgbuf *qbuf, long type){
        qbuf->mtype = type;
        msgrcv(qid, (struct msgbuf *)qbuf, MAX_SEND_SIZE, type, 0);
        printf("Text in stack: %s\n", qbuf->mtext);
}

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    key_t key;
    int qtype = 1;
    struct mymsgbuf qbuf;

    char *str = (char *) malloc(sizeof(char) * 10);

    key = ftok(".", 'm');
    if((msgqid = msgget(key, IPC_CREAT|0660)) == -1) {
        perror("msgget");
        exit(1);
    }    

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");



    
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {   

        sprintf(str, "%s", echoBuffer);
        send_message(msgqid, (struct mymsgbuf *)&qbuf, qtype, str);
        read_message(msgqid, &qbuf, qtype);

        /* Echo message back to client */
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");

        /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");


    }

    close(clntSocket);    /* Close client socket */
}
