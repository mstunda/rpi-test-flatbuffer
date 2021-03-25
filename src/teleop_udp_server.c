/*
        demo-udp-03: udp-recv: a simple udp server
	receive udp messages

        usage:  udp-recv

        Paul Krzyzanowski
*/

#include "teleop_udp_server.h"



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


void teleop_udp_server_listen(char *p_buffer, int *p_recvlength)
{
		printf("waiting on port %d\n", SERVICE_PORT);
		*p_recvlength = recvfrom(fd, p_buffer, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (*p_recvlength > 0) { 
			printf("rx ok!\n"); }
		else printf("rx failed!\n");
}

void teleop_udp_server_report(char *p_buffer, int length)
{
		printf("sending response \"%s\"\n", p_buffer);
		if (sendto(fd, p_buffer, length, 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
}
