#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/ether.h>
#include <linux/if_packet.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INTERFACE "enp6s0"
#define SPORT 6666
#define DPORT 5000

#define MY_DEST_MAC0 0x70
#define MY_DEST_MAC1 0x71
#define MY_DEST_MAC2 0xbc
#define MY_DEST_MAC3 0xd8
#define MY_DEST_MAC4 0x36
#define MY_DEST_MAC5 0x24


unsigned short csum(unsigned short *buf, int nwords)
{
    unsigned long sum;
    for(sum=0; nwords>0; nwords--)
        sum += *buf++;
    sum = (sum >> 16) + (sum &0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

int main(int argc, char const *argv[])
{
	int sockfd, tx_len = 0;
	char sendbuf[1024], *msg;

	memset(sendbuf, 0, 1024);

	struct ifreq if_idx;
	struct ifreq if_mac;
	struct ifreq if_ip;
	struct sockaddr_ll socket_address;

	struct ether_header *eh = (struct ether_header *) sendbuf;
	struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
	struct udphdr *udph = (struct udphdr *) (sendbuf + sizeof(struct iphdr) + sizeof(struct ether_header));

	/* Data */
	msg = (char *) malloc(sizeof(char)*20);
	msg = "Hello raw friend!\0";
	memcpy(sendbuf+sizeof(struct ether_header)+sizeof(struct iphdr)+sizeof(struct udphdr), msg, strlen(msg));
	tx_len += strlen(msg);


	/* Open RAW socket to send on */
	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_UDP)) == -1)
		perror("socket");

	/* Index of the interface */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, INTERFACE, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
		perror("SIOCGIFINDEX");

	/* Get MAC of the interface*/
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, INTERFACE, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
		perror("SIOCGIFHWADDR");

	/* Get IP of the interface */
	memset(&if_ip, 0, sizeof(struct ifreq));
	strncpy(if_ip.ifr_name, INTERFACE, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFADDR, &if_ip) < 0)
		perror("SIOCGIFADDR");

	/* Ethernet header*/

	// eh->ether_shost[0] = (uint8_t) if_mac.ifr_hwaddr.sa_data[0];
	// eh->ether_shost[1] = (uint8_t) if_mac.ifr_hwaddr.sa_data[1];
	// eh->ether_shost[2] = (uint8_t) if_mac.ifr_hwaddr.sa_data[2];
	// eh->ether_shost[3] = (uint8_t) if_mac.ifr_hwaddr.sa_data[3];
	// eh->ether_shost[4] = (uint8_t) if_mac.ifr_hwaddr.sa_data[4];
	// eh->ether_shost[5] = (uint8_t) if_mac.ifr_hwaddr.sa_data[5];

	eh->ether_shost[0] = 0x00;
	eh->ether_shost[1] = 0x1e;
	eh->ether_shost[2] = 0x67;
	eh->ether_shost[3] = 0x46;
	eh->ether_shost[4] = 0xbf;
	eh->ether_shost[5] = 0x19;

	eh->ether_dhost[0] = MY_DEST_MAC0;
	eh->ether_dhost[1] = MY_DEST_MAC1;
	eh->ether_dhost[2] = MY_DEST_MAC2;
	eh->ether_dhost[3] = MY_DEST_MAC3;
	eh->ether_dhost[4] = MY_DEST_MAC4;
	eh->ether_dhost[5] = MY_DEST_MAC5;
	eh->ether_type = htons(ETH_P_IP);
	tx_len += sizeof(struct ether_header);

	/* IP header*/

	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0; // Low delay
	iph->id = htons(50206);
	iph->frag_off = 0x40;
	iph->ttl = 64; // hops
	iph->protocol = IPPROTO_UDP; // UDP
//	iph->saddr = inet_addr(inet_ntoa(((struct sockaddr_in *)&if_ip.ifr_addr)->sin_addr));
	iph->saddr = inet_addr("192.168.1.1");
	iph->daddr = inet_addr("192.168.1.3");
	iph->check = 0;
	tx_len += sizeof(struct iphdr);

	/* UDP header*/

	udph->source = htons(SPORT);
	udph->dest = htons(DPORT);
	udph->len = htons(8 + strlen(msg));
	udph->check = 0; // skip
	tx_len += sizeof(struct udphdr);

	/* Checksums  */
	iph->tot_len = htons(tx_len-sizeof(struct ether_header));

	iph->check = csum((unsigned short *)(sendbuf+sizeof(struct ether_header)), sizeof(struct iphdr)/2);
	udph->check = csum((unsigned short*)udph , 8); 

	/* Index of the network device */
	socket_address.sll_ifindex = if_idx.ifr_ifindex;

	/* Address length*/
	socket_address.sll_halen = ETH_ALEN;

	/* Destination MAC */
	socket_address.sll_addr[0] = MY_DEST_MAC0;
	socket_address.sll_addr[1] = MY_DEST_MAC1;
	socket_address.sll_addr[2] = MY_DEST_MAC2;
	socket_address.sll_addr[3] = MY_DEST_MAC3;
	socket_address.sll_addr[4] = MY_DEST_MAC4;
	socket_address.sll_addr[5] = MY_DEST_MAC5;



	/* Send packet */
	if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
		printf("Send failed\n");

	return 0;
}
