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

int general(){

	char buf[60];

	struct iphdr *iph = (struct iphdr *) buf;
	struct igmphdr *igmph = (struct igmphdr *) (buf + sizeof(struct ip));
	struct sockaddr_in sin;

	int s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

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

	sendto (s, buf, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin));

	close(s);
	return 0;
}

int specific(){

	char buf[60];

	struct iphdr *iph = (struct iphdr *) buf;
	struct igmphdr *igmph = (struct igmphdr *) (buf + sizeof(struct ip));
	struct sockaddr_in sin;

	int s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

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
	igmph-> group = inet_addr("224.0.0.5");

	igmph-> csum = csum((unsigned short *)igmph, sizeof(struct igmphdr));

	sendto (s, buf, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin));

	close(s);
	return 0;
}

int main(int argc, char const *argv[])
{	
	//general();
	specific();
}