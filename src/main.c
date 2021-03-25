#include <stdio.h>

#include "teleop_cmd.h"
#include "teleop_udp_server_api.h"
#include "teleop_flatbuf_server_api.h"

	
	// ToDo: check if rx_buffer_size is big enough ?




int main(int argc, char *argv[]){
	printf("hi\n");	
			
	// Buffer variables for UDP				
	// ToDo: move to udp.h
	char rx_buf[BUFSIZE];	// packed flatbuffer received over udp
  	int rx_length;			// received udp length
	void *tx_buf;			// Gets allocated upon finalizing flatbuffer 
	size_t tx_length; 		// length of buffer to be sent on udp
	

	// Initialize flatbuffer
	teleop_flatbuf_init();
	// Initialize udp
	teleop_udp_server_init();
	
	// Structures holding current commanded and feedback values
	// ToDO - make global for callbacks to access
	states_commanded_s states_commanded;	//@ teleop_cmd.h
	states_feedback_s states_feedback;
		
	// RECEIVE values UDP->FLATBUFFER->Struct
	while(1){
		printf("While loop begun\n");


		// RECEIVE AND UNPACK
		teleop_udp_server_listen(rx_buf, &rx_length);
		printf("Received udp message - ptr: %d, len: %d", (int)rx_buf, (int)rx_length);	
		teleop_flatbuf_unpack_commanded(&states_commanded, rx_buf);


		// Mirror command to feedback
		states_feedback.angle_1 = states_commanded.angle_1;
		states_feedback.angle_2 = states_commanded.angle_2;
		states_feedback.velocity = states_commanded.acceleration;

		printf("Commanded: angle_1: %f, ange_2: %f, acceleration: %f ", 
							states_commanded.angle_1, 
							states_commanded.angle_2, 
							states_commanded.acceleration);
		



		// PACK AND SEND
		// ToDo: remove printfs
		tx_buf = teleop_flatbuf_pack_feedback(&states_feedback, &tx_length); 
		printf("Flatbuffer feedback packed. Address: %d, Length: %d \n", 
												(int)tx_buf, (int)tx_length);

		teleop_udp_server_report(tx_buf, (int)tx_length);  
		printf("Flatbuffer sent\n");
		
		// Reset buffer 
		teleop_flatbuf_reset(tx_buf);
		printf("Flatbuffer reset\n");


	}
	
	
	
	return(0);
}
