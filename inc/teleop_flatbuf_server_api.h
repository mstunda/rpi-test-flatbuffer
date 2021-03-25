#ifndef TELEOP_FLATBUF_SERVER_API_H
#define TELEOP_FLATBUF_SERVER_API_H

#include "teleop_cmd.h"

#include "teleop_car_builder.h"
#include "teleop_types_builder.h"
#include "teleop_car_reader.h"
#include "teleop_types_reader.h"
#include "flatbuffers_common_builder.h"
#include "flatbuffers_common_reader.h"


flatcc_builder_t builder, *B;

void teleop_flatbuf_init();
void teleop_flatbuf_reset(void *p_buffer);
void teleop_flatbuf_server_deinit();

void* teleop_flatbuf_pack_feedback(	states_feedback_s *p_states,
									size_t *p_tx_length);
int teleop_flatbuf_unpack_commanded(	states_commanded_s *p_states,
										void *p_rx_buffer);




#endif // TELEOP_FLATBUF_SERVER_API_H