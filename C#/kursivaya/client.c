/*Клиент 1го типа*/

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXRECVSTRING 255  /* Longest string to receive */
#define RCVBUFSIZE 32      /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* External error handling function */

int main(int argc, char *argv[])
{
	int sock;                         /* Socket */

	struct sockaddr_in broadcastAddr; /* Broadcast Address */
	unsigned short broadcastPort;     /* Broadcast port */
	char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
	int recvStringLen;                /* Length of received string */

	struct sockaddr_in src_addr;	  /* Echo server address */
	unsigned short src_port;     	  /* Echo server port */
	char *servIP;                     /* Server IP address (dotted quad) */
	char *echoString;                 /* String to send to echo server */
	char echoBuffer[RCVBUFSIZE];      /* Buffer for echo string */
	unsigned int echoStringLen;       /* Length of string to echo */
	int bytesRcvd, totalBytesRcvd;    /* Bytes read in single recv() and total bytes read */

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	broadcastPort = htons(2000);

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

	servIP = inet_ntoa(src_addr.sin_addr);    /* First arg: server IP address (dotted quad) */
	echoString = "tcp strings generate";      /* Second arg: string to echo */
	src_port = 2500;			              /* Use given port */

	/* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	/* Construct the server address structure */
	src_addr.sin_family      = AF_INET;             /* Internet address family */
	src_addr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
	src_addr.sin_port        = htons(src_port); 	/* Server port */

	if (connect(sock, (struct sockaddr *) &src_addr, sizeof(src_addr)) < 0)
		DieWithError("connect() failed");

	echoStringLen = strlen(echoString);             /* Determine input length */

	if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
		DieWithError("send() sent a different number of bytes than expected");

	/* Receive the same string back from the server */
	totalBytesRcvd = 0;
	printf("TCP Received: ");                           /* Setup to print the echoed string */
	while (totalBytesRcvd < echoStringLen)
	{
		/* Receive up to the buffer size (minus 1 to leave space for a null terminator) bytes from the sender */
		if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
			DieWithError("recv() failed or connection closed prematurely");

		totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
		echoBuffer[bytesRcvd] = '\0';  /* Terminate the string! */
		printf("%s\n", echoBuffer);    /* Print the echo buffer */
	}

	close(sock);
	exit(0);
}