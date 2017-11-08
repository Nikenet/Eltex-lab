#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/in.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

#define SPORT 6666
#define	DPORT 1500

unsigned short csum(unsigned short *ptr,int nbytes) 
{
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

int main (int argc, char const *argv[])
{
	if( argc < 3){
		printf("Syntax: <source ip> <destination ip>\n");
		exit(0);
	}

	/* Creating raw socket */ 
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
	if(s == -1){
		perror("Failed to create raw socket");
		exit(1);
	}

	char datagram[4096] , source_ip[32] , dest_ip[32], *data;	 

	memset (datagram, 0x00, 4096);
	memset (source_ip, 0x00, 32);
	memset (dest_ip, 0x00, 32);	 

	struct iphdr *iph = (struct iphdr *) datagram;
	struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));	 
	struct sockaddr_in sin;

	/* Part of data */
	data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
	strcpy(data , "hello_from_raw_socket");
	
	strcpy(source_ip , argv[1]);
	strcpy(dest_ip, argv[2]);

	/* Kernel provide Ethernet header for us */
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	sin.sin_addr.s_addr = *dest_ip;

	/* IP header and checksum*/ 
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
	iph->id = htonl (54321);
	iph->frag_off = 0;
	iph->ttl = 255;
	iph->protocol = IPPROTO_UDP;	
	iph->saddr = inet_addr ( source_ip );
	iph->daddr = inet_addr ( dest_ip );
	iph->check = 0;

	iph->check = csum ((unsigned short *)datagram, iph->tot_len);

	/* UDP header and checksum */ 
	udph->source = htons (SPORT);
	udph->dest = htons (DPORT);
	udph->len = htons(8 + strlen(data));
	udph->check = 0;

	udph->check = csum((unsigned short*)udph , 8); 

	/* Sending */
	if (sendto (s, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
		perror("sendto failed");
	else
		printf ("Sended message: %s, from %s, to %s\n", data, source_ip, dest_ip);

	return 0;
}
