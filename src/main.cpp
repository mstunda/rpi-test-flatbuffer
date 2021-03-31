#include <stdio.h>
#include <thread>
#include <chrono> 
#include <unistd.h> // for usleep
#include <mutex>

extern "C"
{
#include "teleop_cmd.h"
#include "teleop_udp_server.h"
#include "teleop_flatbuf_server.h"
}


#define OSX_DEBUGGING


unsigned char rx_buf[BUFSIZE];	// packed flatbuffer received over udp
int rx_length;			// received udp length
void *tx_buf;			// Gets allocated upon finalizing flatbuffer 
size_t tx_length; 		// length of buffer to be sent on udp

void teleop_udp_server();
	

int main(int argc, char *argv[])
{
	printf("hi\n");	
	
	//int port = argc == 2 ? atoi(argv[1]) : SERVICE_PORT;
			
	// Buffer variables for UDP				
	// ToDo: move to?
	

	teleop_flatbuf_init();
	teleop_udp_server_init();


	///////////////////////////////////////
	///////  RECEIVE UDP COMMANDS	///////		(update states_command)
	///////////////////////////////////////

	std::thread t1(teleop_udp_server);



	while(1)
	{
		
#ifdef OSX_DEBUGGING
		// Mirror command to feedback
		states_feedback.angle_1 = states_commanded.angle_1;
		states_feedback.angle_2 = states_commanded.angle_2;
		states_feedback.velocity = states_commanded.acceleration;
#endif

		printf("\n\n\n\nCOMMANDS - angle_1: %lf, angle_2: %lf, acceler.: %lf \nFEEDBACK - angle_1: %f, angle_2: %f, velocity: %f \n", 	
		states_commanded.angle_1, states_commanded.angle_2,	states_commanded.acceleration,
		states_feedback.angle_1, states_feedback.angle_2, states_feedback.velocity);



		///////////////////////////////////
		///////  SEND CAN COMMANDS	///////		(states_command - updated in parallel thread)
		///////////////////////////////////






		///////////////////////////////////
		///////  SEND UDP FEEDBACK	///////		(states_feedback - updated in Callbacks)
		///////////////////////////////////

		tx_buf = teleop_flatbuf_pack_feedback(&states_feedback, &tx_length); 
		teleop_udp_server_report((unsigned char *)tx_buf, (int)tx_length);  
		teleop_flatbuf_reset(tx_buf);


		usleep(100E3);

	}
	
	t1.join();
	
	return(0);
}




void teleop_udp_server()
{
	while(1)
	{

		teleop_udp_server_listen(rx_buf, &rx_length);
		printf("Received udp message - ptr: %ld, len: %d\n", (long)rx_buf, (int)rx_length);	
		teleop_flatbuf_unpack_commanded(&states_commanded, rx_buf);

	}
}