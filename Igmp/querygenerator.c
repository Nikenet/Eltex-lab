#include <linux/igmp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

#define MIN_IP_HEADER_LEN 20

unsigned short csum(unsigned short *ptr,int nbytes){
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum=0;
	while(nbytes>1) {
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;
	 
	return(answer);
}

const unsigned long hash(const char *str) {
	unsigned long hash = 5381;  
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}


int general( char *interface){

	char buf[60];

	struct iphdr *iph = (struct iphdr *) buf;
	struct igmphdr *igmph = (struct igmphdr *) (buf + sizeof(struct ip));
	struct sockaddr_in sin;

	int s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (s == -1)
		perror("Failed to create raw socket");
	
	if((setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, interface, strlen(interface))) < 0)
		perror("setsockopt error");

	/* Kernel provide Ethernet header for us */
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("224.0.0.1");

	/* IP header and checksum*/ 
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof(struct igmphdr);
	iph->frag_off = 0;
	iph->ttl = 1;
	iph->protocol = IPPROTO_IGMP;
	iph->saddr = inet_addr("0.0.0.0");
	iph->daddr = inet_addr("224.0.0.1");
	iph->check = 0;

	iph->check = csum ((unsigned short *)buf, iph->tot_len);

	/* IGMP header and checksum */
	igmph-> type = 0x11;
	igmph-> code = 100;
	igmph-> csum = 0;
	igmph-> group = inet_addr("0.0.0.0");

	igmph-> csum = csum((unsigned short *)igmph, sizeof(struct igmphdr));

	if ((sendto (s, buf, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin))) < 0)
		perror("sendto failed");

	close(s);
	return 0;
}

int specific(char *ip, char *interface){

	char buf[60];

	struct iphdr *iph = (struct iphdr *) buf;
	struct igmphdr *igmph = (struct igmphdr *) (buf + sizeof(struct ip));
	struct sockaddr_in sin;

	int s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (s == -1)
		perror("Failed to create raw socket");
	
	if ((setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, interface, strlen(interface))) < 0)
		close(s);

	/* Kernel provide Ethernet header for us */
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);

	/* IP header and checksum*/ 
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof(struct igmphdr);
	iph->frag_off = 0;
	iph->ttl = 1;
	iph->protocol = IPPROTO_IGMP;
	iph->saddr = inet_addr("0.0.0.0");
	iph->daddr = inet_addr("224.0.0.1");
	iph->check = 0;

	iph->check = csum ((unsigned short *)buf, iph->tot_len);

	/* IGMP header and checksum */
	igmph-> type = 0x11;
	igmph-> code = 100;
	igmph-> csum = 0;
	igmph-> group = inet_addr(ip);

	igmph-> csum = csum((unsigned short *)igmph, sizeof(struct igmphdr));

	if ((sendto (s, buf, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin))) < 0)
		perror("sendto failed");

	close(s);
	return 0;
}

int main(int argc, char **argv){	

	int go;
	
	char *ip = NULL;
	char *interface = NULL;
	char *type = NULL;

	if(argc == 1){

		printf("Usage: [-t <type of packet>][-i <interface>] [-a <IP address>] [-h <HELP>]\n\n");
		return 0;

	} else {
		while((go = getopt(argc, argv, "t:i:a:hv")) != -1)
			switch(go){
				case 'i':
					interface = optarg;
					break;
				case 'a':
					ip = optarg;
					break;
				case 't':
					type = optarg;
					break;
				case 'h':
					printf("\nOptions:\n");
					printf("\t-t\tType of the IGMP Query <(gen)(spec)>");
					printf("\t\tWith type general(gen) dont need -a\n");
					printf("\t-i\tName of ethernet interface\n");
					printf("\t-a\tIP group addresses\n\n");
					printf("\t-h\tOpen this page\n");
					printf("\t-v\tVersion of program\n\n");
					return 0;
				case 'v':
					printf("\n\tCreated by Nikita Mikhailov <Nikenet1@gmail.com>\n");
					printf("\tVersion: 1.1\n\n");
					return 0;
				default:
					printf("\tUnknown options character, see -h \n");
					return 0;
			}
	}

	if (argc < 4 ){
		printf("Need to use -i with -t, -a need only for <spec> see -h\n");
		return 0;
	} else {
		if(hash(type) == hash("gen"))
			general(interface);
		else if (hash(type) == hash("spec"))
			specific(ip, interface);
		else
			printf("Unknow character %lu\n", hash(type));
	}	
}