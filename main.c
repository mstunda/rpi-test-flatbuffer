#include <stdio.h>


#include "flatbuf-teleop/src/c_h/teleop_car_builder.h"
#include "flatbuf-teleop/src/c_h/teleop_types_builder.h"
#include "flatbuf-teleop/src/c_h/teleop_car_reader.h"
#include "flatbuf-teleop/src/c_h/teleop_types_reader.h"
#include "flatbuf-teleop/src/c_h/flatbuffers_common_builder.h"
#include "flatbuf-teleop/src/c_h/flatbuffers_common_reader.h"


// A helper to simplify creating vectors from C-arrays.
#define c_vec_len(V) (sizeof(V)/sizeof((V)[0]))
// This allows us to verify result in optimized builds.
#define test_assert(x) do { if (!(x)) { assert(0); return -1; }} while(0)




int main(int argc, char *argv[]){
	printf("hi\n");	
	
    flatcc_builder_t builder, *B; 	// builder object
	B = &builder;
    void  *tx_buf;					// actual buffer to be sent away 
    size_t tx_buffer_size;				
	
    flatcc_builder_init(&builder);

	// Load info to builder
	
	float tx_angle_f = 1.4;
	float tx_angle_r = 1.3;
	float tx_accel = 1.5;
	
	// Create Control request
	getugo_VehicleControlRequest_ref_t tx_control_request;
	tx_control_request = getugo_VehicleControlRequest_create(B, tx_angle_f, tx_angle_r, tx_accel);
	// Assign Control request to Payload
	getugo_Payload_union_ref_t tx_payload;
	tx_payload = getugo_Payload_as_VehicleControlRequest(tx_control_request);
	
	// Dummy header?
	int64_t tx_timestamp = 1;
	getugo_Header_t tx_header = {tx_timestamp};
	
	getugo_TeleopMsg_create_as_root(B, &tx_header, tx_payload);
	
	
	/*
	
	// Create TeleopMsg from Payload
	
	getugo_TeleopMsg_start_as_root(B);
	getugo_TeleopMsg_payload_VehicleControlRequest_add(B, tx_control_request);
	getugo_TeleopMsg_end_as_root(B);
	
	
	
	*/
	
	// Create buffer
    tx_buf = flatcc_builder_finalize_aligned_buffer(&builder, &tx_buffer_size);
	
	// Send buffer
	
	teleop_udp_server_respond(buf, BUFSIZE);		
	
	
	// Receive buffer
	int rx_buffer_size = 0; 
	teleop_udp_server_listen(rx_buf, &rx_buffer_size);
	// ToDo: check if rx_buffer_size is big enough ?
	
	// Access Buffer
	
	getugo_TeleopMsg_table_t rx_teleop_message = getugo_TeleopMsg_as_root (tx_buf);
	test_assert (rx_teleop_message != 0);
	
	
	
	//if(getugo_TeleopMsg_Payload_type_name == "VehicleControlRequest"){
		getugo_VehicleControlRequest_table_t rx_control_request;
		rx_control_request = (getugo_VehicleControlRequest_table_t) getugo_TeleopMsg_payload(rx_teleop_message); 
	
	
		float rx_angle_f = getugo_VehicleControlRequest_steering_angle(rx_control_request);
		float rx_angle_r = getugo_VehicleControlRequest_steering_angle_rear_axle(rx_control_request);
		float rx_accel = getugo_VehicleControlRequest_acceleration(rx_control_request);
	
		
		printf("Angle 1: %f, Angle2: %f, Accel: %f", rx_angle_f, rx_angle_r, rx_accel);
		
		
		//}
	

	
	
	// Free and Reset buffer 
    flatcc_builder_aligned_free(tx_buf);
    // For reusing
	flatcc_builder_reset(&builder);
    
	// Eventually
	flatcc_builder_clear(&builder);
	
	
	
	return(0);
}
