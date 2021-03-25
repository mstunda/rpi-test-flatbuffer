#ifndef TELEOP_UDP_SERVER_API_H
#define TELEOP_UDP_SERVER_API_H

#define SERVICE_PORT	21234	/* hard-coded port number */
#define BUFSIZE 2048


int teleop_udp_server_init();
void teleop_udp_server_listen(unsigned char *p_buffer, int *length);
void teleop_udp_server_report(unsigned char *p_buffer, int length);


#endif // TELEOP_UDP_SERVER_API_H
