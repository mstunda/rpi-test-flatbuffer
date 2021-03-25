#include <stdio.h>

#include "teleop_cmd.h"
#include "teleop-udp-server.h"
#include "teleop-flatbuf-api.h"

	
	// ToDo: check if rx_buffer_size is big enough ?




int main(int argc, char *argv[]){
	printf("hi\n");	
					
					
    
					
					
	// Buffer variables for UDP				
	
	//void *rx_buf ;	
	char rx_buf[BUFSIZE];// <-- packed flatbuffer received over udp
  	int rx_length;			// received udp length
	
	void *tx_buf;	// Gets allocated upon finalizing flatbuffer 
	//char tx_buf[BUFFSIZE]//	<-- packed flatbuffer sent over udp

	size_t tx_length; // length of buffer to be sent on udp
	

	// Initialize flatbuffer
	teleop_flatbuf_init();
	// Initialize udp
	teleop_udp_server_init();
	printf("socket fd after init: %d, addrlen: %d \n", fd, addrlen);
	
	//ToDo: remove after debug
	teleop_udp_client_local_init();

	// Structures holding current commanded and feedback values
	// ToDO - make global for callbacks to access
	states_commanded_s states_commanded_udp;	//@ teleop_cmd.h
	states_feedback_s states_feedback_udp, states_feedback_udp_2;

	states_feedback_udp.angle_1 = 1.1;
	states_feedback_udp.angle_2 = 1.2;
	states_feedback_udp.velocity = 1.3;
	
	
	// RECEIVE values UDP->FLATBUFFER->Struct
	while(1){
		printf("While loop begun\n");
		// swapped sequence for initial testing


		//teleop_udp_server_listen(rx_buf, &rx_length);	

		//teleop_flatbuf_unpack_commanded(rx_buf, &states_commanded_udp);   @teleop-flatbuf-api.h


		tx_buf = teleop_flatbuf_pack_feedback(&states_feedback_udp, &tx_length); 
		printf("Flatbuffer packed. Address: %d, Length: %d \n", 
								(int)tx_buf,
								(int)tx_length);

		teleop_udp_server_report(tx_buf, (int)tx_length);  
		printf("Flatbuffer sent\n");
		
		// Reset buffer 
		teleop_flatbuf_reset(tx_buf);
		printf("Flatbuffer reset\n");
		
		printf("socket fd before listen: %d, addrlen: %d \n", fd, addrlen);

		teleop_udp_server_listen(rx_buf, &rx_length);	
		
		printf("socket fd after listen: %d \n", fd);

		
		printf("UDP received\n");

		teleop_flatbuf_unpack_feedback(rx_buf, &states_feedback_udp_2); //  @teleop-flatbuf-api.h
		
		printf("angle_1: %f, ange_2: %f, velocity: %f ", 
							states_feedback_udp_2.angle_1, 
							states_feedback_udp_2.angle_2, 
							states_feedback_udp_2.velocity);
		
	}
	
	
	
	return(0);
}
