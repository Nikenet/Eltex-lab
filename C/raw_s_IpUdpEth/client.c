#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<netinet/in.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include<netinet/ether.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<sys/ioctl.h>
#include<linux/if_packet.h>
#include<linux/if_ether.h>


#define SPORT 6666
#define	DPORT 2000
#define TMPSIZE 1024
#define BINDPORT 6666
#define HEADESIZE (sizeof(struct iphdr)+sizeof(struct udphdr))

#define DEFAULT_IF	"enp6s0"

#define D_MAC0	0xAA
#define D_MAC1	0xAA
#define D_MAC2	0xBB
#define D_MAC3	0xBB
#define D_MAC4	0xCC
#define D_MAC5	0xCC

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

int snd (char source_ip[32], char dest_ip[32]){



	char datagram[4096], *data;
	memset (datagram, 0x00, 4096);

	struct ether_header *eh = (struct ether_header *) datagram;
	struct iphdr *iph = (struct iphdr *) (datagram + sizeof(struct ether_header));
	struct udphdr *udph = (struct udphdr *) (datagram + sizeof(struct ether_header) + sizeof(struct iphdr));
	struct sockaddr_ll socket_address;

	/* Creating raw socket */ 
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
	if(s == -1){
		perror("Failed to create raw socket");
		exit(1);
	}

	struct ifreq if_idx;
	struct ifreq if_mac;
	int tx_len = 0;

	/* Interface name */
	char ifName[IFNAMSIZ];
	strcpy(ifName, DEFAULT_IF);

	/* Part of data */
	data = datagram + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
	strcpy(data , "hello_from_raw_socket");

	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(s, SIOCGIFINDEX, &if_idx) < 0)
	    perror("SIOCGIFINDEX");

	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(s, SIOCGIFHWADDR, &if_mac) < 0)
		perror("SIOCGIFHWADDR");

	/* Ethernet header */
	eh->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
	eh->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
	eh->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
	eh->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
	eh->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
	eh->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];

	eh->ether_dhost[0] = D_MAC0;
	eh->ether_dhost[1] = D_MAC1;
	eh->ether_dhost[2] = D_MAC2;
	eh->ether_dhost[3] = D_MAC3;
	eh->ether_dhost[4] = D_MAC4;
	eh->ether_dhost[5] = D_MAC5;

	/* Ethertype field */
	eh->ether_type = htons(ETH_P_IP);
	tx_len += sizeof(struct ether_header)+ sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);

	/* Destination MAC */
	socket_address.sll_addr[0] = D_MAC0;
	socket_address.sll_addr[1] = D_MAC1;
	socket_address.sll_addr[2] = D_MAC2;
	socket_address.sll_addr[3] = D_MAC3;
	socket_address.sll_addr[4] = D_MAC4;
	socket_address.sll_addr[5] = D_MAC5;

	/* Index of the network device */
	socket_address.sll_ifindex = if_idx.ifr_ifindex;

	/* Address length*/
	socket_address.sll_halen = ETH_ALEN;

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
	if (sendto (s, datagram, tx_len ,  0, (struct sockaddr *)&socket_address, sizeof(struct sockaddr_ll)) < 0)
		perror("sendto failed");
	else
		printf ("Sended message: %s, from %s, to %s\n", data, source_ip, dest_ip);

	close(s);

	return 0;
}

int main (int argc, char *argv[])
{
	if( argc < 3){
		printf("Syntax: <source ip> <destination ip>\n");
		exit(0);
	}

	snd(argv[1], argv[2]);
	
}
