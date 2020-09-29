#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/ip_icmp.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<linux/if_packet.h>
#include<net/ethernet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

void print_packet(unsigned char* buffer, int size);

int main()
{
	int saddr_size , data_size;
	struct sockaddr saddr;
	unsigned char *buffer = (unsigned char *)malloc(65536);
	printf("Starting...\n");
	int socketfd = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));
	if(socketfd < 0)
	{
		perror("Socket Error");
		return 0;
	}
	while(1)
	{
		saddr_size = sizeof saddr;
		//Receive a packet
		data_size = recvfrom(socketfd , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
		if(data_size <0 )
		{
			printf("Recvfrom error , failed to get packets\n");
			return 1;
		}
		print_packet(buffer , data_size);
	}
	printf("Finished");
	return 0;
}

void print_packet(unsigned char* buffer, int size)
{
	struct iphdr *iph = (struct iphdr*)buffer;
	printf("%d",(*iph).protocol);
	if((*iph).protocol = 6){ // icmp id
		printf("ICMP packet: ");
		printf("-TTL: %d-", (*iph).ttl);
	}
}