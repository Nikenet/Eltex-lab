#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/in.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

#define TMPSIZE 1024
#define BINDPORT 2000
#define HEADESIZE (sizeof(struct iphdr)+sizeof(struct udphdr))

int main (int argc, char *argv[])
{	
	if( argc < 2){
		printf("Syntax: <ip address to bind>\n");
		exit(0);
	}

	/* Creating raw socket */ 
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(s == -1){
		perror("Failed to create raw socket");
		exit(1);
	}

	setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, "lo", 2);

	struct sockaddr_in sin;
	char tmp[TMPSIZE];
    ssize_t msglen;
	socklen_t socklen;

	memset (tmp, 0x00, TMPSIZE);
	memset (&sin, 0x00, sizeof(struct sockaddr_in));

	/* Needed to bind */
	sin.sin_family = AF_INET;
	sin.sin_port = htons(BINDPORT);
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	socklen = (socklen_t) sizeof(sin);

    /* Bind to port*/
    printf("Binding...\n");	
	int b = bind(s, (struct sockaddr*)&sin, socklen);
	if ( b == -1){
		perror("Cannot bind");
		return 1;
	}
    /* Start to recieve*/
    printf("Recieving...\n");
	msglen = recvfrom(s, tmp, TMPSIZE, 0, 0, 0);
	if (msglen == -1){
		perror("Cannot recieve");
		return 1;
	}

	tmp[msglen] = '\0';
	printf("Data: %s\n", tmp+HEADESIZE);

	return 0;
}