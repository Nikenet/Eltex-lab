/* Сервер */

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <sys/types.h>  /* for pthread_t type */
#include "TCPEchoServer.h"  /* TCP echo server includes */
#include <pthread.h>        /* for POSIX threads */


#define MAXPENDING 5    /* Maximum outstanding connection requests */

struct ThreadArgs
{
    int clntSock;                      /* Socket descriptor for client */
};

void DieWithError(char *errorMessage);  /* External error handling function */
void HandleTCPClient(int clntSocket);   /* TCP client handling function */
void *ThreadMain(void *arg);            /* Main program of a thread */

void *UdpBroadcastSender(void *arg){

	int sock;                         /* Socket */
	struct sockaddr_in broadcastAddr; /* Broadcast address */
	char *broadcastIP;                /* IP broadcast address */
	unsigned short broadcastPort;     /* Server port */
	const char *sendString;           /* String to broadcast */
	int broadcastPermission;          /* Socket opt to set permission to broadcast */
	unsigned int sendStringLen;       /* Length of string to broadcast */

	broadcastIP = "192.168.2.255";    /* First arg:  broadcast IP address */ 
	broadcastPort = htons(2000);      /* Second arg:  broadcast port */
	sendString = "Hey one";           /* Third arg:  string to broadcast */

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	broadcastPermission = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0)
		DieWithError("setsockopt() failed");

	memset(&broadcastAddr, 0, sizeof(broadcastAddr));       /* Zero out structure */
	broadcastAddr.sin_family = AF_INET;                     /* Internet address family */
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP); /* Broadcast IP address */
	broadcastAddr.sin_port = broadcastPort;                 /* Broadcast port */
	sendStringLen = strlen(sendString);                     /* Find length of sendString */
	
	for (;;){ /* Run forever */
	
		if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
			DieWithError("sendto() sent a different number of bytes than expected");
	}
}

void *ThreadMain(void *threadArgs)
{
    int clntSock;                   /* Socket descriptor for client connection */

    /* Guarantees that thread resources are deallocated upon return */
    pthread_detach(pthread_self()); 

    /* Extract socket file descriptor from argument */
    clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
    free(threadArgs);              /* Deallocate memory for argument */

    HandleTCPClient(clntSock);

    return (NULL);
}

// void *TcpConnection(void *arg){

// 	int servSock;                    /* Socket descriptor for server */
// 	int clntSock;                    /* Socket descriptor for client */
// 	struct sockaddr_in echoServAddr; /* Local address */
// 	struct sockaddr_in echoClntAddr; /* Client address */
// 	unsigned short echoServPort;     /* Server port */
// 	unsigned int clntLen;            /* Length of client address data structure */

// 	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
// 		DieWithError("socket() failed");

// 	echoServPort = htons(2500);
	  
// 	memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
// 	echoServAddr.sin_family = AF_INET;                /* Internet address family */
// 	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
// 	echoServAddr.sin_port = echoServPort;             /* Local port */

// 	if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
// 		DieWithError("bind() failed");

// 	if (listen(servSock, MAXPENDING) < 0)
// 		DieWithError("listen() failed");

// 	for (;;) /* Run forever */
// 	{
// 		/* Set the size of the in-out parameter */
// 		clntLen = sizeof(echoClntAddr);

// 		/* Wait for a client to connect */
// 		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
// 			DieWithError("accept() failed");

// 		/* clntSock is connected to a client! */

// 		printf("TCP Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
// 		HandleTCPClient(clntSock);
// 	}
// }

/* Structure of arguments to pass to client thread */

void *TcpConnection(void *arg)
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    unsigned short echoServPort;     /* Server port */
    pthread_t threadID;              /* Thread ID from pthread_create() */
    struct ThreadArgs *threadArgs;   /* Pointer to argument structure for thread */

    echoServPort = 2500;  /* First arg:  local port */

    servSock = CreateTCPServerSocket(echoServPort);

    for (;;) /* run forever */
    {
	clntSock = AcceptTCPConnection(servSock);

        /* Create separate memory for client argument */
        if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs))) == NULL)
            DieWithError("malloc() failed");

        threadArgs -> clntSock = clntSock;

        /* Create client thread */
        if (pthread_create(&threadID, NULL, ThreadMain, (void *) threadArgs) != 0)
            DieWithError("pthread_create() failed");

        printf("with thread %ld\n", (long int) threadID);
    }
    /* NOT REACHED */
}



int main(int argc, char *argv[])
{	
	int count = 2;            /* Count of thread */
	pthread_t threads[count]; /* Thread descriptor */
	void *status[count];      /* Status of thread */


	pthread_create(&threads[1], NULL, UdpBroadcastSender, 0); /* Start UDP broadcast sender */
	pthread_create(&threads[2], NULL, TcpConnection, 0);	  /* Start TCP connections listener*/

	pthread_join(threads[1], &status[1]);  /* Wait UDP broadcast sender */                   
	pthread_join(threads[2], &status[2]);  /* Wait TCP connections listener*/

	
}
