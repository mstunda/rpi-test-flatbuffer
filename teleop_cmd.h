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






#endif // TELEOP_CMD_H