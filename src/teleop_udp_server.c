/*
        demo-udp-03: udp-recv: a simple udp server
	receive udp messages

        usage:  udp-recv

        Paul Krzyzanowski
*/

#include "teleop_udp_server.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>



static int fd = -1;								// socket for udp
static struct sockaddr_in myaddr, remaddr;	// local addresss
static socklen_t addrlen;					// address length


int teleop_udp_server_init()
{
	addrlen = sizeof(remaddr);
	
	// create a UDP socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("cannot create socket\n");
		return 0;
		
	}

	// BIND the socket to any valid IP address and pick a specific PORT
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		return 0;
	}
		
	return 1;
	
}


void teleop_udp_server_listen(unsigned char *p_buffer, int *p_recvlength)
{
		if(fd == -1){
			int ret = teleop_udp_server_init();
		}
		
		printf("waiting on port %d\n", SERVICE_PORT);
		*p_recvlength =  recvfrom(fd, p_buffer, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (*p_recvlength > 0) { 
		//	printf("rx ok!\n"); 
		}
		else printf("rx failed!\n");
}

void teleop_udp_server_report(unsigned char *p_buffer, int length)
{
	//	printf("sending response");
		if (sendto(fd, p_buffer, length, 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
}
