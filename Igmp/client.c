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
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <net/if.h>
#include <time.h>

#define SIZEOFIP 32
#define SIZEOFDATAGRAM 100
#define TTL 1
#define IP "192.168.2.6"
#define MAXCOUNTGROUPIP 500
#define ADD 193486030
#define	DEL 193489338
#define MIN_IP_HEADER_LEN 20

/* Massive of IP group address */
char *rngip[MAXCOUNTGROUPIP];
int rngiplen = 0, rngipcount = 0;

/* Struct with sockets file descriptors */
struct arg_struct {
	int sr;
	int ss;
};

/* Function, needs to redefenition byte IP to string representation */
static char *ipToStr (unsigned int ip, char *buffer){

	sprintf (buffer, "%d.%d.%d.%d",

		ip & 0xff,
		(ip >> 8) & 0xff,
		(ip >> 16) & 0xff,		
		ip >> 24
	);

	return buffer;
}

/* Calculate strings hash */
const unsigned long hash(const char *str) {
	unsigned long hash = 5381;  
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

/* Function calculate header checksum */
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

/* Generate IGMP report packet*/
int igmpv2_report(int sock, char destIP[SIZEOFIP], char groupIP[SIZEOFIP]){

	char datagram[SIZEOFDATAGRAM];
	memset (datagram, 0x00, SIZEOFDATAGRAM);

	struct iphdr *iph = (struct iphdr *) datagram;
	struct igmphdr *igmph = (struct igmphdr *) (datagram + sizeof(struct ip));
	struct sockaddr_in sin;

	/* Kernel provide Ethernet header for us */
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(destIP);

	/* IP header and checksum*/ 
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof(struct igmphdr);
	iph->frag_off = 0;
	iph->ttl = TTL;
	iph->protocol = IPPROTO_IGMP;	
	iph->daddr = inet_addr(destIP);
	iph->saddr = inet_addr(IP);
	iph->check = 0;

	iph->check = csum ((unsigned short *)datagram, iph->tot_len);

	/* IGMP header and checksum */
	igmph-> type = IGMPV2_HOST_MEMBERSHIP_REPORT;
	igmph-> code = 0;
	igmph-> csum = 0;
	igmph-> group = inet_addr(groupIP);

	igmph-> csum = csum((unsigned short *)igmph, sizeof(struct igmphdr));

	/* Sending */
	if (sendto (sock, datagram, iph->tot_len ,  0,
				(struct sockaddr *) &sin, sizeof (sin)) < 0){

		perror("sendto failed");
		return -1;

	} else
		printf ("CLIENT: Sended IGMP Report to %s group %s\n", destIP , groupIP);	

	return 0;
}

/* Generate IGMP leave packet*/
int igmpv2_leave(int sock, char destIP[SIZEOFIP], char groupIP[SIZEOFIP]){

	char datagram[SIZEOFDATAGRAM];
	memset (datagram, 0x00, SIZEOFDATAGRAM);

	struct iphdr *iph = (struct iphdr *) datagram;
	struct igmphdr *igmph = (struct igmphdr *) (datagram + sizeof(struct ip));
	struct sockaddr_in sin;

	/* Kernel provide Ethernet header for us */
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(destIP);

	/* IP header and checksum*/ 
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof(struct igmphdr);
	iph->frag_off = 0;
	iph->ttl = TTL;
	iph->protocol = IPPROTO_IGMP;	
	iph->daddr = inet_addr(destIP);
	//iph->saddr = inet_addr(IP);
	iph->check = 0;

	iph->check = csum ((unsigned short *)datagram, iph->tot_len);

	/* IGMP header and checksum */
	igmph-> type = IGMP_HOST_LEAVE_MESSAGE;
	igmph-> code = 0;
	igmph-> csum = 0;
	igmph-> group = inet_addr(groupIP);

	igmph-> csum = csum((unsigned short *)igmph, sizeof(struct igmphdr));

	/* Sending */
	if (sendto (sock, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin,
				sizeof (sin)) < 0){

		perror("sendto failed");
		return -1;

	} else
		printf ("CLIENT: Sended IGMP Leave to %s group %s\n",destIP , groupIP );	

	return 0;
}

int listener(int ss, int sr){

	int random;
	int recvcount = 0;
	int delaycount = 0;

	char buf[100];
	char buftoip[16];

	memset(buf, 0x00, 100);
	memset(buftoip, 0x00, 16);

	struct iphdr *iph = (struct iphdr *) buf;
	struct igmphdr *igmph = (struct igmphdr *) (buf + sizeof(struct ip));

	while(1){

		if ((recvfrom(sr, buf, 100, 0, 0, 0)) == -1)
			perror("Recv failed");

		/* Destruct packet */
		if (igmph -> type == 0x11){
			
			if (igmph -> group != 0x00){

				printf("CLIENT: Recieved IGMP Group specific query ");
				printf("from %s ", ipToStr(iph->saddr, buftoip));
				printf("\n        group %s ",ipToStr(igmph->group, buftoip));
				printf("MaxRespTime %d\n", igmph->code);

				/* Send report to specific group */
				for (int j = 0; j < rngiplen; ++j){					
					if (strcmp(ipToStr(igmph->group, buftoip), rngip[j]) == 0){

						srand (time(NULL));
						random = rand() % igmph->code;
						printf("CLIENT: [*] to group %s sets delay value in %d second\n",
						ipToStr(igmph->group, buftoip), random/10);
						sleep(random/10);
						igmpv2_report(ss, rngip[j], rngip[j]);	
					}				
				}

				printf("CLIENT: Whaiting IGMP Query\n");

				memset(buf, 0x00, 100);
				return 0;
				
			} else {

				int timer[rngiplen];
				srand (time(NULL));

				printf("CLIENT: Recieved IGMP Query ");
				printf("from %s ", ipToStr(iph->saddr, buftoip));
				printf("MaxRespTime %d\n", igmph->code);

				/* Set personal delay to all group */
				for (int j = 0; j < rngiplen; ++j){

					random = rand() % igmph->code;
					timer[j] = random / 10;
					if (hash(rngip[j]) != hash("0.0.0.0"))
						printf("CLIENT: [%d] to group %s sets delay value in %d second\n",
								j, rngip[j], timer[j]);
					delaycount++;					
				}

				/* Send report to all actual group */
				for(int i = 0; i <= igmph->code/10; ++i){
					for(int j = 0; j < rngiplen; ++j){
						recvcount++;
						if (hash(rngip[j]) != hash("0.0.0.0")){
								if(timer[j] == i){
								igmpv2_report(ss, rngip[j], rngip[j]);
							}							
							
						}
					}


						sleep(1);

				}

				printf("CLIENT: Whaiting IGMP Query\n");

				memset(buf, 0x00, 100);
				return 0;
			}				
		}
	}
}

/* Parse stdin (add, del)*/
void *commands(void *arg){

	int socket = *(int*)arg;
	char wordstdin[16];

	while(1){

		fgets(wordstdin, 20, stdin);
		char *ins = strtok(wordstdin," ");
		
		switch(hash(ins)){
			case ADD:

				ins = strtok(NULL," ");
				ins = strtok(ins,"\n");

				rngip[rngiplen] = (char *) malloc (sizeof(char)*16);
				strcpy(rngip[rngiplen], ins);

				igmpv2_report(socket, rngip[rngiplen], rngip[rngiplen]);
				rngiplen++;

				break;
			case DEL:
				
				ins = strtok(NULL," ");
				ins = strtok(ins,"\n");

				for (int j = 0; j < rngiplen; ++j){
					if (hash(ins) == hash(rngip[j])){
						igmpv2_leave(socket, rngip[j], rngip[j]);
						rngip[j] = "0.0.0.0";
						break;
					}
				}
				
				break;
			default:
				printf("CLIENT: Unknown characters %lu\n", hash(ins));
				break;
		}
	}

	pthread_exit(0);
}

int main(int argc, char **argv){

	int result, go, i=0;
	pthread_t threads;

	char *ip = NULL;
	char *interface = NULL;	

	char *mip1 = NULL;
	char *mip2 = NULL;
	char *mip3 = NULL;
	char *mip4 = NULL;

	char *fts1 = NULL;
	char *fts2 = NULL;

	struct arg_struct *args = malloc(sizeof(struct arg_struct));

	struct ifreq if_idx;

	if(argc == 1){

		printf("Usage: [-i <interface>] [-a <IP address>] [-h <HELP>]\n\n");
		return 0;

	} else {
		while((go = getopt(argc, argv, "i:a:hv")) != -1)
			switch(go){
				case 'i':
					interface = optarg;
					break;
				case 'a':
					ip = optarg;
					break;
				case 'h':
					printf("\nOptions:\n");
					printf("\t-i\tName of ethernet interface\n");
					printf("\t-a\tRange of IP addresses <0.0.0.0 or 0.0.0.0-255>\n\n");
					printf("\tadd\tInput IP address of group\n");
					printf("\tdel\tDel IP address of group\n\n");
					printf("\t-h\tOpen this page\n");
					printf("\t-v\tVersion of program\n\n");
					return 0;
				case 'v':
					printf("\n\tCreated by Nikita Mikhailov <Nikenet1@gmail.com>\n");
					printf("\tVersion: 1.0\n\n");
					return 0;
				default:
					printf("\tUnknown options character, see -h \n");
					return 0;
			}
	}

	if (argc < 4){
		printf("Need to use -i with -a, see -h\n");
		return 0;
	} else {

		/* Start work */
		/* Socket to recieve with IPPROTO_IGMP */
		args -> sr = socket(AF_INET, SOCK_RAW, IPPROTO_IGMP);
		if(args -> sr == -1){
			perror("Failed to create raw socket");
			exit(1);
		}

		/* Socket to send with IPPROTO_RAW*/
		args -> ss = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
		if(args -> ss == -1){
			perror("Failed to create raw socket");
			exit(1);
		}
		
		memset(&if_idx, 0, sizeof(if_idx));
		strncpy(if_idx.ifr_name, interface, sizeof(if_idx.ifr_name));
		if (setsockopt(args -> ss, SOL_SOCKET, SO_BINDTODEVICE, &if_idx, 
						sizeof(if_idx)) < 0) { 

			close(args -> ss);
		}

		memset(&if_idx, 0, sizeof(if_idx));
		strncpy(if_idx.ifr_name, interface, sizeof(if_idx.ifr_name));
		if (setsockopt(args -> sr, SOL_SOCKET, SO_BINDTODEVICE, &if_idx, 
						sizeof(if_idx)) < 0) { 

			close(args -> sr);
		}

		/* Parse range of ip (flag -a)*/
		char *ins = strtok(ip, ".");
			
		if (ins != NULL){

			mip1 = ins;
			mip2 = strtok(NULL, ".");
			mip3 = strtok(NULL, ".");
			mip4 = strtok(NULL, ".");

			ins = strtok(mip4, "-");

			if (ins != NULL){

				fts1 = ins;
				fts2 = strtok(NULL, "-");
			}
		}

		if (fts2 != NULL){

			int f1 = atoi(fts1);
			int f2 = atoi(fts2);

			while(f1 <= f2){

				rngip[i] = (char *) malloc (sizeof(char)*16);
				memset(rngip[i], 0x00, 16);
				sprintf(rngip[i], "%s.%s.%s.%d", mip1, mip2, mip3, f1);				
				
				/* Sending report */
				igmpv2_report(args -> ss, rngip[i], rngip[i]);

				f1++;
				i++;
				rngiplen++;
			}

		} else {

			int f1 = atoi(fts1);

			rngip[i] = (char *) malloc (sizeof(char)*16);
			memset(rngip[i], 0x00, 16);
			sprintf(rngip[i], "%s.%s.%s.%d", mip1, mip2, mip3, f1);				
				
			/* Sending report */
			igmpv2_report(args -> ss, rngip[i], rngip[i]);
			i++;
			rngiplen++;
		}

		result = pthread_create(&threads, NULL, commands, &args->ss);
		if (result != 0) {
			perror("Error reating the first thread");
			return EXIT_FAILURE;
		}


		while(1){

			listener(args -> ss, args -> sr);

		}	
	}
}