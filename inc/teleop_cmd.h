#ifndef TELEOP_CMD_H
#define TELEOP_CMD_H

typedef struct{
	float angle_1;
	float angle_2;
	float acceleration;
} states_commanded_s;

typedef struct{
	float angle_1;
	float angle_2;
	float velocity;
} states_feedback_s;

// Structures holding current commanded and feedback values
// ToDO - make global for callbacks to access
states_commanded_s states_commanded;	//@ teleop_cmd.h
states_feedback_s states_feedback;




#endif 
// TELEOP_CMD_H
