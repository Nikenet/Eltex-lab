#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "message.pb-c.h"

#define MAX_MSG_SIZE	  14
#define MAXRECVSTRING     100   /* Longest string to receive */
#define RCVBUFSIZE        14   /* Size of receive buffer */
#define BPORTFORMANAGERS  2002  /* Broadcast port for managers*/
#define PORTFORMANAGERS   1500  /* Port to TCP connections for managers*/


void DieWithError(char *errorMessage);  /* External error handling function */

int main(int argc, char *argv[])
{	
	DMessage   *msg;         // DMessage using submessages
	Submessage *sub1;	   // Submessages

	int sock;                         /* Socket */

	struct sockaddr_in broadcastAddr; /* Broadcast Address */
	unsigned short broadcastPort;     /* Broadcast port */
	char *recvString; /* Buffer for received string */
	int recvStringLen;                /* Length of received string */	

	int i=0;
	uint8_t buf[MAX_MSG_SIZE]; // Input data container for bytes

	struct sockaddr_in src_addr;	  /* Echo server address */
	unsigned short src_port;     	  /* Echo server port */
	char *servIP;                     /* Server IP address (dotted quad) */
	int bytesRcvd;					  /* Bytes read in single recv() and total bytes read */

	recvString = (char *) malloc(sizeof(char) * MAXRECVSTRING);
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	broadcastPort = htons(BPORTFORMANAGERS);

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
	src_port = PORTFORMANAGERS;			      /* Use given port */

	/* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	/* Construct the server address structure */
	src_addr.sin_family      = AF_INET;             /* Internet address family */
	src_addr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
	src_addr.sin_port        = htons(src_port); 	/* Server port */

	if (connect(sock, (struct sockaddr *) &src_addr, sizeof(src_addr)) < 0)
		DieWithError("connect() failed");

	bytesRcvd = recv(sock, buf, RCVBUFSIZE, 0);
	
	printf("Start TCP recieving\n");

	while (bytesRcvd > 0){

		msg = dmessage__unpack(NULL, RCVBUFSIZE, buf); // Deserialize the serialized input
		if (msg == NULL){ // Something failed
		    fprintf(stderr,"error unpacking incoming message\n");
		}
		sub1 = msg->a;

		++i;		
		printf("[%d]\tTCP recieved:\t%s\t%p\n", i, sub1->value, buf);

		if ((bytesRcvd = recv(sock, buf, RCVBUFSIZE, 0)) < 0)
			DieWithError("recv() failed");

		dmessage__free_unpacked(msg,NULL);
	}
	close(sock);
}
