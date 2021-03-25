/*
        demo-udp-03: udp-recv: a simple udp server
	receive udp messages

        usage:  udp-recv

        Paul Krzyzanowski
*/

#include "teleop-udp-server.h"



int teleop_udp_server_init()
{
	addrlen = sizeof(remaddr);
	
	// create a UDP socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		printf("cannot create socket\n");
		return 0;
		
	}

	printf("socket fd in init: %d, addrlen: %d \n", fd, addrlen);


	// bind the socket to any valid IP address and pick any port
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);
	
	// ToDo: as server, switch to specific port
	// bind the socket to any valid IP address and a specific port
	//myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		printf("bind failed");
		return 0;
	}
	
	printf("socket fd at initialization: %d \n", fd);
	
	
	return 1;
	
}


int teleop_udp_client_local_init()
{
	char *server = "127.0.0.1";
	memset((char *) &remaddr, 0, sizeof(remaddr));
	
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
	printf("remaddr successful \n");
	return 1;
}




void teleop_udp_server_listen(char *p_buffer, int *p_recvlength)
{
		printf("waiting on port \n"); //ToDo - reset msg " %d\n", SERVICE_PORT);
		*p_recvlength = recvfrom(fd, p_buffer, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (*p_recvlength > 0) { 
			printf("rx ok!\n"); }
		else printf("uh oh - something went wrong!\n");
}

void teleop_udp_server_report(char *p_buffer, int length)
{
		printf("sending response \"%s\"\n", p_buffer);
		if (sendto(fd, p_buffer, length, 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
}
