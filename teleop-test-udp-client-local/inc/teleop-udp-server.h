#ifndef TELEOP_UDP_SERVER_H
#define TELEOP_UDP_SERVER_H

#define SERVICE_PORT	21234	/* hard-coded port number */
#define BUFSIZE 2048


void teleop_udp_server_init();
void teleop_udp_server_listen(char *p_buffer, int *length);
void teleop_udp_server_respond(char *p_buffer, int length);


#endif // TELEOP_UDP_SERVER_H
