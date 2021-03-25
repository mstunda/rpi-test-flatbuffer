#include "teleop-flatbuf-api.h"
#include <stdio.h>

// A helper to simplify creating vectors from C-arrays.
#define c_vec_len(V) (sizeof(V)/sizeof((V)[0]))
// This allows us to verify result in optimized builds.
#define test_assert(x) do { if (!(x)) { assert(0); return -1; }} while(0)



// Note that we use the `table_t` suffix when reading a table object
// as opposed to the `ref_t` suffix used during the construction of
// the buffer.


void teleop_flatbuf_init()
{
	B = &builder;
	flatcc_builder_init(B);
}

void teleop_flatbuf_reset(void *p_buffer)
{
	// Free and Reset buffer 
	flatcc_builder_aligned_free(p_buffer);
	// For reusing
	flatcc_builder_reset(B);
}

void teleop_flatbuf_deinit()
{
	// Eventually
	flatcc_builder_clear(B);
}


/**
 *	Create flatbuffer from feedback states struct
 *  
 *
 *
 **/

void* teleop_flatbuf_pack_feedback(	states_feedback_s *p_states,
									size_t *p_tx_length)
{
	void *p_tx_buffer; 
	// Create TABLE - VehicleTelemetryUpdate 
	getugo_VehicleTelemetryUpdate_ref_t tx_telemetry_update = 
		getugo_VehicleTelemetryUpdate_create(	B, 
												p_states->velocity, 
												p_states->angle_1, 
												p_states->angle_2);
	
	printf("v: %f, a1: %f, a2: %f \n", 	p_states->velocity, 
										p_states->angle_1, 
										p_states->angle_2);
										
	printf("B: %d \n", (int)B);									
	// Assign VehicleTelemetryUpdate to UNION - Payload  
	getugo_Payload_union_ref_t tx_payload = 
		getugo_Payload_as_VehicleTelemetryUpdate(tx_telemetry_update);

	// Dummy STRUCT - Header 
	int64_t tx_timestamp = 0;
	getugo_Header_t tx_header = {tx_timestamp};

	// Create TABLE - TeleopMsg  = Header + Payload
	getugo_TeleopMsg_create_as_root(B, &tx_header, tx_payload);
	
	
	// Create buffer in memory - return pointer
	p_tx_buffer = flatcc_builder_finalize_aligned_buffer(B, p_tx_length);
	printf("Flatbuffer just packed. Address: %d \n", (int)p_tx_buffer);
	
	return p_tx_buffer;
	
}

/**
 *	Create flatbuffer from commanded states struct
 *  
 *
 *
 **/
/*
void teleop_flatbuf_pack_commanded(void *p_tx_buffer, states_commanded_s *p_states){
	// Create control request
	getugo_VehicleControlRequest_ref_t tx_control_request;
	tx_control_request = getugo_VehicleControlRequest_create(B, tx_angle_f, tx_angle_r, tx_accel);
	// Assign Control request to Payload
	getugo_Payload_union_ref_t tx_payload;
	tx_payload = getugo_Payload_as_VehicleControlRequest(tx_control_request);

	// Dummy header?
	int64_t tx_timestamp = 1;
	getugo_Header_t tx_header = {tx_timestamp};

	getugo_TeleopMsg_create_as_root(B, &tx_header, tx_payload);
	
	// Create buffer
	p_tx_buffer = flatcc_builder_finalize_aligned_buffer(&builder, &tx_buffer_size);
	
	
}

*/




/**
 *	UNPACK flatbuffer into feedback states struct
 *  
 *
 *
 **/

int teleop_flatbuf_unpack_feedback(void *p_rx_buffer, states_feedback_s *p_states)
{
	// Access buffer as teleop message
	getugo_TeleopMsg_table_t rx_teleop_message = getugo_TeleopMsg_as_root (p_rx_buffer);
	test_assert (rx_teleop_message != 0);

	////  if(getugo_TeleopMsg_Payload_type_name == "VehicleTelemetryUpdate"){
	
	// Parse TABLE - VehicleTelemetryUpdate - from Payload
	getugo_VehicleTelemetryUpdate_table_t rx_telemetry_update = 
		(getugo_VehicleTelemetryUpdate_table_t) getugo_TeleopMsg_payload(rx_teleop_message); 

	// Extract reported values from VehicleTelemetryUpdate
	p_states->angle_1 = getugo_VehicleTelemetryUpdate_actual_angle(rx_telemetry_update);
	p_states->angle_2 = getugo_VehicleTelemetryUpdate_actual_angle_rear_axle(rx_telemetry_update);
	p_states->velocity = getugo_VehicleTelemetryUpdate_velocity(rx_telemetry_update);
	
	//// }
	
	return 1;
	
}


/**
 *	UNPACK flatbuffer from commanded states struct
 *  
 *
 *
 **/
/*
void teleop_flatbuf_unpack_commanded(void *p_rx_buffer, states_commanded_s *p_states){

	// Access buffer as teleop message
	getugo_TeleopMsg_table_t rx_teleop_message = getugo_TeleopMsg_as_root (p_rx_buffer);
	test_assert (rx_teleop_message != 0);

	////  if(getugo_TeleopMsg_Payload_type_name == "VehicleControlRequest"){
	
		// Parse control request from message
		getugo_VehicleControlRequest_table_t rx_control_request;
		rx_control_request = (getugo_VehicleControlRequest_table_t) getugo_TeleopMsg_payload(rx_teleop_message); 

		// Extract commanded values from control request
		p_states->angle_1 = getugo_VehicleControlRequest_steering_angle(rx_control_request);
		p_states->angle_2 = getugo_VehicleControlRequest_steering_angle_rear_axle(rx_control_request);
		p_states->acceleration = getugo_VehicleControlRequest_acceleration(rx_control_request);
	
	//// }
	
}

*/








/*

// Create TeleopMsg from Payload

getugo_TeleopMsg_start_as_root(B);
getugo_TeleopMsg_payload_VehicleControlRequest_add(B, tx_control_request);
getugo_TeleopMsg_end_as_root(B);



*/