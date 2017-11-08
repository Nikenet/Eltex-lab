#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){

	int message[1];
	int sock;
	struct sockaddr_in addr;
	const char *ip = "127.0.0.1";

	message[1] = 0;	

	srand (9999);
	int random = rand() % 5;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0){
		printf("socket error\n");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(1500); //порт
	addr.sin_addr.s_addr = inet_addr(ip);

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		printf("connect error\n");
		exit(2);
	}

	while(1){

		random = rand() % 5;

		sleep(random);
		message[0]=random;

		send(sock, message, sizeof(message), 0);

		printf("Random sleep\t%d\t1st sended\t%d\n", random, message[0]);

	}

	close(sock);
}