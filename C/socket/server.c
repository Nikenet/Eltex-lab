#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

int main(){
	
	int sock, listener;
	struct sockaddr_in addr;
	int buf[1];
	int bytes_read;
	int i=0, total=10;
	const char *ip = "127.0.0.1";

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0){
		printf("socket\n");
		exit(1);
	}

	srand (5555);
	int random = rand() % 5;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1500); //порт
	addr.sin_addr.s_addr = inet_addr(ip);

	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		printf("bind\n");
		exit(2);
	}

	listen(listener, 1);
	
	while(1){

		sock = accept(listener, NULL, NULL);

		if(sock < 0){
			printf("accept\n");
			exit(3);
		}

		while(1){

			bytes_read = recv(sock, buf, 4, 0);	

			if(bytes_read <= 0){break;} 

			i++;
			buf[1] = random = rand() % 5;
			total = total-buf[0]+buf[1];

			if (total <= 0)
			{
				printf("\t\tExit\n"	);
			}
			printf("#%d\t1st\t%d\t2nd\t%d\ttotal\t%d\n", i, buf[0], buf[1], total);
	
		}	
		close(sock);
	}	
	return 0;
}
