#ifndef TELEOP_UDP_SERVER_H
#define TELEOP_UDP_SERVER_H

#define SERVICE_PORT	21234	/* hard-coded port number */
#define BUFSIZE 2048

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int fd;						// socket for udp
struct sockaddr_in myaddr;				// local address
socklen_t addrlen;				// address length

// ToDo: remove after testing:
struct sockaddr_in remaddr;				// remote address



int teleop_udp_server_init();
void teleop_udp_server_listen(char *p_buffer, int *length);
void teleop_udp_server_report(char *p_buffer, int length);

//ToDo: Remove after debug
int teleop_udp_client_local_init();


#endif // TELEOP_UDP_SERVER_H
