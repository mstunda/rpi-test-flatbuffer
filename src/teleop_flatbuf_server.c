#include "teleop_flatbuf_server.h"
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
									size_t *p_length)
{
	void *p_buffer; 
	// Create TABLE - VehicleTelemetryUpdate 
	getugo_VehicleTelemetryUpdate_ref_t telemetry_update = 
		getugo_VehicleTelemetryUpdate_create(	B, 
												p_states->velocity, 
												p_states->angle_1, 
												p_states->angle_2);
										
	// Assign VehicleTelemetryUpdate to UNION - Payload  
	getugo_Payload_union_ref_t payload = 
		getugo_Payload_as_VehicleTelemetryUpdate(telemetry_update);

	// Dummy STRUCT - Header 
	int64_t timestamp = 0;
	getugo_Header_t header = {timestamp};

	// Create TABLE - TeleopMsg  = Header + Payload
	getugo_TeleopMsg_create_as_root(B, &header, payload);
	
	
	// Create buffer in memory - return pointer
	p_buffer = flatcc_builder_finalize_aligned_buffer(B, p_length);
	printf("Flatbuffer just packed. Address: %d \n", (int)p_buffer);
	return p_buffer;
	
}

/**
 *	UNPACK flatbuffer from commanded states struct
 *  
 *
 *
 **/

int teleop_flatbuf_unpack_commanded(states_commanded_s *p_states, void *p_buffer){

	// Parse TABLE - TeleopMsg from buffer
	getugo_TeleopMsg_table_t teleop_message = getugo_TeleopMsg_as_root (p_buffer);
	test_assert (teleop_message != 0);

	////  ToDo: if(getugo_TeleopMsg_Payload_type_name == "VehicleControlRequest"){
	
		// Parse TABLE - VehicleControlRequest - from Payload of TeleopMsg
		getugo_VehicleControlRequest_table_t control_request = 
			(getugo_VehicleControlRequest_table_t) getugo_TeleopMsg_payload(teleop_message); 

		// Extract commanded values from VehicleControlRequest
		p_states->angle_1 = getugo_VehicleControlRequest_steering_angle(control_request);
		p_states->angle_2 = getugo_VehicleControlRequest_steering_angle_rear_axle(control_request);
		p_states->acceleration = getugo_VehicleControlRequest_acceleration(control_request);
	
	//// }
		
	return 1;
}








/*

// Create TeleopMsg from Payload

getugo_TeleopMsg_start_as_root(B);
getugo_TeleopMsg_payload_VehicleControlRequest_add(B, tx_control_request);
getugo_TeleopMsg_end_as_root(B);



*/