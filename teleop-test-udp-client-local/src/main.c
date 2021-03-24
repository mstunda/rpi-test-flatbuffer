#include "../inc/teleop-udp-server.h"
#include <stdio.h>


char buf[BUFSIZE];				// rx buffer
int recvlength = 0;					// No. of bytes received

int main(int argc, char **argv)
{
	teleop_udp_server_init();
	
	while(1){
		teleop_udp_server_listen(buf, &recvlength);

		buf[recvlength] = 0;
		printf("received message: \"%s\" (%d bytes)\n", buf, recvlength);
		
		teleop_udp_server_respond(buf, BUFSIZE);		
	}
}	