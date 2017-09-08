#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include <time.h>

#define MAXRECVSTRING     255   /* Longest string to receive */
#define BPORTFORCLIENTS   2001  /* Broadcast port for clients*/
#define PORTFORCLIENTS    2500  /* Port to TCP connections for clients*/
#define STRNGLEN          69    /* Count of char that needs to generate random string*/

void DieWithError(char *errorMessage);  /* External error handling function */

/* Random string generator */
char *randstring(int length) {    
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    size_t stringLen = STRNGLEN;        
    char *randomString;

    randomString = malloc(sizeof(char) * (length +1));

    if (!randomString) {
        return (char*)0;
    }

    unsigned int key = 0;

    for (int n = 0;n < length;n++){            
        key = rand() % stringLen;          
        randomString[n] = string[key];
    }

    randomString[length] = '\0';

    return randomString;
}

int main(int argc, char *argv[])
{
	int sock;                         /* Socket */
	struct sockaddr_in broadcastAddr; /* Broadcast Address */
	unsigned short broadcastPort;     /* Broadcast port */
	char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
	int recvStringLen;                /* Length of received string */

	int i=0;

	struct sockaddr_in src_addr;	  /* Echo server address */
	unsigned short src_port;     	  /* Echo server port */
	char *servIP;                     /* Server IP address (dotted quad) */
	char *echoString;                 /* String to send to echo server */
	unsigned int echoStringLen;       /* Length of string to echo */

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	broadcastPort = htons(BPORTFORCLIENTS);

	memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
	broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
	broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */
	broadcastAddr.sin_port = broadcastPort;             /* Broadcast port */

	if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
		DieWithError("bind() failed");

	socklen_t src_addr_len = sizeof(src_addr);
	memset(&src_addr, 0x00, src_addr_len);

	if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, (struct sockaddr *) &src_addr, &src_addr_len)) < 0)
		DieWithError("recvfrom() failed");

	recvString[recvStringLen] = '\0';
	printf("UDP Broadcdas received: %s\n", recvString);      		 /* Print the received string */
	printf("Server address: %s\n", inet_ntoa(src_addr.sin_addr));	 /* Print source ip */

	close(sock);

	servIP = inet_ntoa(src_addr.sin_addr);    /* server IP address (dotted quad) */
	src_port = PORTFORCLIENTS;			      /* Use given port */

	/* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	/* Construct the server address structure */
	src_addr.sin_family      = AF_INET;             /* Internet address family */
	src_addr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
	src_addr.sin_port        = htons(src_port); 	/* Server port */

	if (connect(sock, (struct sockaddr *) &src_addr, sizeof(src_addr)) < 0)
		DieWithError("connect() failed");	

	printf("Start TCP sending\n");
	for (;;){

		++i;
		echoString = randstring(10);             
		echoStringLen = strlen(echoString);             

		printf("[%d]\tTCP sended:\t%s\n", i, echoString);
		
		if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
			DieWithError("send() sent a different number of bytes than expected");	                 

		sleep(3);
	}	
}
