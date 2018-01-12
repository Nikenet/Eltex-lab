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
#include <pthread.h>
#include <signal.h>

#define SIZEOFIP 32
#define SIZEOFDATAGRAM 60
#define TTL 64

static char *ipToStr (unsigned int ip, char *buffer){

	sprintf (buffer, "%d.%d.%d.%d",

		ip & 0xff,
		(ip >> 8) & 0xff,
		(ip >> 16) & 0xff,		
		ip >> 24
	);

	return buffer;
}

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

int  igmpv2_query(int sock, char destIP[SIZEOFIP], char groupIP[SIZEOFIP]){

	char datagram[SIZEOFDATAGRAM];
	memset (datagram, 0x00, SIZEOFDATAGRAM);

	struct iphdr *iph = (struct iphdr *) datagram;
	struct igmphdr *igmph = (struct igmphdr *) (datagram + sizeof(struct ip));
	struct sockaddr_in sin;

	/* Kernel provide Ethernet header for us */
	sin.sin_family = AF_INET;

	/* IP header and checksum*/ 
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof(struct igmphdr);
	iph->frag_off = 0;
	iph->ttl = TTL;
	iph->protocol = IPPROTO_IGMP;	
	iph->daddr = inet_addr(destIP);
	iph->check = 0;

	iph->check = csum ((unsigned short *)datagram, iph->tot_len);

	/* IGMP header and checksum */
	igmph-> type = IGMP_HOST_MEMBERSHIP_QUERY;
	igmph-> code = 0;
	igmph-> csum = 0;
	igmph-> group = inet_addr(groupIP);

	igmph-> csum = csum((unsigned short *)igmph, sizeof(struct igmphdr));

	/* Sending */
	if (sendto (sock, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0){

		perror("sendto failed");
		return -1;

	} else
		printf ("SERVER: Sended IGMP Query\n");	

	return 0;
}

int listener(int sock){
	
	char buf[60];
	char buftoip[16];

	memset(buf, 0x00, 60);
	memset(buftoip, 0x00, 16);

	struct iphdr *iph = (struct iphdr *) buf;
	struct igmphdr *igmph = (struct igmphdr *) (buf + sizeof(struct ip));
	
	recvfrom(sock, buf, 60, 0, 0, 0);		

	/* Destruct packet */

	if (igmph->type == IGMP_HOST_LEAVE_MESSAGE){

		printf("SERVER: IGMP Leave  ");
		printf("group %s ",ipToStr(igmph-> group, buftoip));
		printf("from %s ", ipToStr(iph->saddr, buftoip));
		printf("to %s\n", ipToStr(iph->daddr, buftoip));

		memset(buf, 0x00, 60);

		return IGMP_HOST_LEAVE_MESSAGE;
		

	} else if (igmph->type == IGMPV2_HOST_MEMBERSHIP_REPORT){

		printf("SERVER: IGMP Report ");
		printf("group %s ",ipToStr(igmph-> group, buftoip));
		printf("from %s ", ipToStr(iph->saddr, buftoip));
		printf("to %s\n", ipToStr(iph->daddr, buftoip));

		memset(buf, 0x00, 60);

		return IGMPV2_HOST_MEMBERSHIP_REPORT;
	}	

	/* If not retuned type of IGMP packet */
	return -1;
}

void *querry(void *arg){

	int s = *(int*)arg;	

	while (1) {

		sleep(2);
		igmpv2_query(s, "224.0.0.1", "0.0.0.0");

	}
}

int main(int argc, char *argv[]){

	int result;
	int clients = 0;
	pthread_t threads;
	int thread_started = 0;

	/* Socket to recieve with IPPROTO_IGMP*/
	int sr = socket(AF_INET, SOCK_RAW, IPPROTO_IGMP);
	if(sr == -1){
		perror("Failed to create raw socket");
		exit(1);
	}

	/* Socket to send with IPPROTO_RAW*/
	int ss = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if(ss == -1){
		perror("Failed to create raw socket");
		exit(1);
	}

	/* Bind to interface */
	setsockopt(sr, SOL_SOCKET, SO_BINDTODEVICE, "enp6s0", 2);
	setsockopt(ss, SOL_SOCKET, SO_BINDTODEVICE, "enp6s0", 2);
	
	printf("SERVER: Waiting clients\n");

	while(1){

		int mtype = listener(sr);

		switch (mtype) {
		case IGMPV2_HOST_MEMBERSHIP_REPORT:
			clients++;
			break;
		case IGMP_HOST_LEAVE_MESSAGE:
			clients--;
			break;
		}

		if (clients) {

			if (thread_started == 1)
				continue;

			//querry_sended = 0;
			result = pthread_create(&threads, NULL, querry, &ss);
			if (result != 0) {
				perror("Error reating the first thread");
				return EXIT_FAILURE;
			}

			thread_started = 1;

		} else {

			printf("SERVER: Have not clients, stop working...\n");
			printf("SERVER: Waiting clients\n");

			if (thread_started == 1) {
				result = pthread_cancel(threads);
				if (result != 0) {
					perror("Error joining the first thread");
					return EXIT_FAILURE;
				}

				thread_started = 0;
			}
		}
	}

	return 0;
}