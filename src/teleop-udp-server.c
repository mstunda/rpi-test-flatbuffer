/*
        demo-udp-03: udp-recv: a simple udp server
	receive udp messages

        usage:  udp-recv

        Paul Krzyzanowski
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../inc/teleop-udp-server.h"



int fd;						// socket for udp
//char buf[BUFSIZE];				// rx buffer
struct sockaddr_in myaddr;				// local address
struct sockaddr_in remaddr;				// remote address
socklen_t addrlen = sizeof(remaddr);	// address length

void teleop_udp_server_init()
{
	
	// create a UDP socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		//return 0;
	}

	// bind the socket to any valid IP address and a specific port
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
	//	return 0;
	}
	
}

void teleop_udp_server_listen(char *p_buffer, int *p_recvlength)
{
		printf("waiting on port %d\n", SERVICE_PORT);
		*p_recvlength = recvfrom(fd, p_buffer, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (*p_recvlength > 0) { 
			printf("rx ok!\n"); }
		else printf("uh oh - something went wrong!\n");
}

void teleop_udp_server_respond(char *p_buffer, int length)
{
		printf("sending response \"%s\"\n", p_buffer);
		if (sendto(fd, p_buffer, length, 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
}
