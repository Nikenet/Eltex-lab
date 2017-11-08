#include <stdio.h>      	/* for printf() and fprintf() */
#include <sys/socket.h> 	/* for socket() and bind() */
#include <arpa/inet.h>  	/* for sockaddr_in */
#include <stdlib.h>     	/* for atoi() and exit() */
#include <string.h>     	/* for memset() */
#include <unistd.h>     	/* for close() */
#include <sys/types.h>		/* for pthread_t type */
#include "TCPEchoServer.h"  /* TCP echo server includes */
#include <pthread.h>        /* for POSIX threads */

#define MAXPENDING        5     /* Maximum outstanding connection requests */
#define BPORTFORCLIENTS   2001  /* Broadcast port for clients*/
#define BPORTFORMANAGERS  2002  /* Broadcast port for managers*/
#define PORTFORCLIENTS    2500  /* Port to TCP connections for clients*/
#define PORTFORMANAGERS   1500  /* Port to TCP connections for managers*/
#define MAX_MSG_SIZE 4096

char *broadcastIP;

struct ThreadArgs{
	int clntSock;		/* Socket descriptor for client */
};

void DieWithError(char *errorMessage);  	/* External error handling function */
void HandleTCPClient(int clntSocket);		/* TCP client handling function */
void HandleTCPManages(int clntSocket);      /* TCP client handling function */

void *UdpBroadcastSenderForClient(void *arg){

	int sock;									/* Socket */
	struct sockaddr_in broadcastAddr;			/* Broadcast address */
	unsigned short broadcastPort;				/* Server port */
	const char *sendString = "UDP to clients";
	int broadcastPermission;					/* Socket opt to set permission to broadcast */
	unsigned int sendStringLen;					/* Length of string to broadcast */

	broadcastPort = htons(BPORTFORCLIENTS);		/* Broadcast port */

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
		sleep(1);
		if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
			DieWithError("sendto() sent a different number of bytes than expected");
	}
}

void *UdpBroadcastSenderForManager(void *arg){

	int sock;									/* Socket */
	struct sockaddr_in broadcastAddr; 			/* Broadcast address */
	unsigned short broadcastPort;				/* Server port */
	const char *sendString = "UDP to manager";
	int broadcastPermission;					/* Socket opt to set permission to broadcast */
	unsigned int sendStringLen;					/* Length of string to broadcast */

	broadcastPort = htons(BPORTFORMANAGERS);	/* Broadcast port */

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
		sleep(1);
		if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
			DieWithError("sendto() sent a different number of bytes than expected");
	}
}

void *ThreadMainClient(void *threadArgs){	
	int clntSock;                   /* Socket descriptor for client connection */

	/* Guarantees that thread resources are deallocated upon return */
	pthread_detach(pthread_self()); 

	/* Extract socket file descriptor from argument */
	clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
	free(threadArgs);              /* Deallocate memory for argument */

	HandleTCPClient(clntSock);
	return 0;
}

void *ThreadMainManager(void *threadArgs){	
	int clntSock;                   /* Socket descriptor for client connection */

	/* Guarantees that thread resources are deallocated upon return */
	pthread_detach(pthread_self()); 

	/* Extract socket file descriptor from argument */
	clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
	free(threadArgs);              /* Deallocate memory for argument */

	for (;;){
		HandleTCPManages(clntSock);
		sleep(3);
	}
	return 0;
} 

void *TcpConnectionClient(void *arg){
	int servSock;                    /* Socket descriptor for server */
	int clntSock;                    /* Socket descriptor for client */
	unsigned short echoServPort;     /* Server port */
	pthread_t threadID;              /* Thread ID from pthread_create() */
	struct ThreadArgs *threadArgs;   /* Pointer to argument structure for thread */
	
	echoServPort = PORTFORCLIENTS;   /* Local port */

	servSock = CreateTCPServerSocket(echoServPort);

	for (;;) /* run forever */
	{
	clntSock = AcceptTCPConnection(servSock);

		if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs))) == NULL)
			DieWithError("malloc() failed");

		threadArgs -> clntSock = clntSock;

		if (pthread_create(&threadID, NULL, ThreadMainClient, (void *) threadArgs) != 0)
			DieWithError("pthread_create() failed");
		
		printf("Create thread to TCP connect with client, ID:\t%ld\n", (long int) threadID);
	}
}

void *TcpConnectionManager(void *arg){
	int servSock;                    /* Socket descriptor for server */
	int clntSock;                    /* Socket descriptor for client */
	unsigned short echoServPort;     /* Server port */
	pthread_t threadID;              /* Thread ID from pthread_create() */
	struct ThreadArgs *threadArgs;   /* Pointer to argument structure for thread */
	
	echoServPort = PORTFORMANAGERS;  /* Local port */

	servSock = CreateTCPServerSocket(echoServPort);

	for (;;) /* run forever */
	{
	clntSock = AcceptTCPConnection(servSock);

		if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs))) == NULL)
			DieWithError("malloc() failed");

		threadArgs -> clntSock = clntSock;

		if (pthread_create(&threadID, NULL, ThreadMainManager, (void *) threadArgs) != 0)
			DieWithError("pthread_create() failed");
		
		printf("Create thread to TCP connect with manager, ID:\t%ld\n", (long int) threadID);
	}
}

int main(int argc, char *argv[]){

	int count = 4;            /* Count of thread */
	pthread_t threads[count]; /* Thread descriptor */
	void *status[count];      /* Status of thread */

	broadcastIP = (char *) malloc(sizeof(char)*15);

	if (argc < 2){
		printf("Syntax: <BroadcastIP>\n");
		return 1;	
	}

	printf("Broadcast IP: %s\n", argv[1]);
	broadcastIP = argv[1];

	pthread_create(&threads[1], NULL, UdpBroadcastSenderForClient, 0);  /* Start UDP broadcast sender */
	pthread_create(&threads[2], NULL, UdpBroadcastSenderForManager, 0); /* Start UDP broadcast sender */

	pthread_create(&threads[3], NULL, TcpConnectionClient, 0);	  /* Start TCP connections listener*/
	pthread_create(&threads[4], NULL, TcpConnectionManager, 0);	  /* Start TCP connections listener*/

	pthread_join(threads[1], &status[1]);  /* Wait UDP broadcast sender */                   
	pthread_join(threads[2], &status[2]);  /* Wait TCP connections listener*/	

	pthread_join(threads[3], &status[3]);  /* Wait UDP broadcast sender */                   
	pthread_join(threads[4], &status[4]);  /* Wait TCP connections listener*/	
}
