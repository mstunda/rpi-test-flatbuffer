#ifndef TELEOP_CAR_READER_H
#define TELEOP_CAR_READER_H

/* Generated by flatcc 0.6.1-dev FlatBuffers schema compiler for C by dvide.com */

#ifndef FLATBUFFERS_COMMON_READER_H
#include "flatbuffers_common_reader.h"
#endif
#ifndef TELEOP_TYPES_READER_H
#include "teleop_types_reader.h"
#endif
#include "flatcc/flatcc_flatbuffers.h"
#ifndef __alignas_is_defined
#include <stdalign.h>
#endif
#include "flatcc/flatcc_prologue.h"
#ifndef flatbuffers_identifier
#define flatbuffers_identifier 0
#endif
#ifndef flatbuffers_extension
#define flatbuffers_extension ".bin"
#endif


typedef const struct getugo_VehicleControlRequest_table *getugo_VehicleControlRequest_table_t;
typedef struct getugo_VehicleControlRequest_table *getugo_VehicleControlRequest_mutable_table_t;
typedef const flatbuffers_uoffset_t *getugo_VehicleControlRequest_vec_t;
typedef flatbuffers_uoffset_t *getugo_VehicleControlRequest_mutable_vec_t;
typedef const struct getugo_VehicleTelemetryUpdate_table *getugo_VehicleTelemetryUpdate_table_t;
typedef struct getugo_VehicleTelemetryUpdate_table *getugo_VehicleTelemetryUpdate_mutable_table_t;
typedef const flatbuffers_uoffset_t *getugo_VehicleTelemetryUpdate_vec_t;
typedef flatbuffers_uoffset_t *getugo_VehicleTelemetryUpdate_mutable_vec_t;
typedef const struct getugo_TeleopMsg_table *getugo_TeleopMsg_table_t;
typedef struct getugo_TeleopMsg_table *getugo_TeleopMsg_mutable_table_t;
typedef const flatbuffers_uoffset_t *getugo_TeleopMsg_vec_t;
typedef flatbuffers_uoffset_t *getugo_TeleopMsg_mutable_vec_t;
#ifndef getugo_VehicleControlRequest_identifier
#define getugo_VehicleControlRequest_identifier flatbuffers_identifier
#endif
#define getugo_VehicleControlRequest_type_hash ((flatbuffers_thash_t)0x2f1f0d8)
#define getugo_VehicleControlRequest_type_identifier "\xd8\xf0\xf1\x02"
#ifndef getugo_VehicleTelemetryUpdate_identifier
#define getugo_VehicleTelemetryUpdate_identifier flatbuffers_identifier
#endif
#define getugo_VehicleTelemetryUpdate_type_hash ((flatbuffers_thash_t)0x5b128bb8)
#define getugo_VehicleTelemetryUpdate_type_identifier "\xb8\x8b\x12\x5b"
#ifndef getugo_TeleopMsg_identifier
#define getugo_TeleopMsg_identifier flatbuffers_identifier
#endif
#define getugo_TeleopMsg_type_hash ((flatbuffers_thash_t)0xb08d0f76)
#define getugo_TeleopMsg_type_identifier "\x76\x0f\x8d\xb0"



struct getugo_VehicleControlRequest_table { uint8_t unused__; };

static inline size_t getugo_VehicleControlRequest_vec_len(getugo_VehicleControlRequest_vec_t vec)
__flatbuffers_vec_len(vec)
static inline getugo_VehicleControlRequest_table_t getugo_VehicleControlRequest_vec_at(getugo_VehicleControlRequest_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(getugo_VehicleControlRequest_table_t, vec, i, 0)
__flatbuffers_table_as_root(getugo_VehicleControlRequest)

__flatbuffers_define_scalar_field(0, getugo_VehicleControlRequest, steering_angle, flatbuffers_float, float, 0.000000f)
__flatbuffers_define_scalar_field(1, getugo_VehicleControlRequest, steering_angle_rear_axle, flatbuffers_float, float, 0.000000f)
__flatbuffers_define_scalar_field(2, getugo_VehicleControlRequest, acceleration, flatbuffers_float, float, 0.000000f)

struct getugo_VehicleTelemetryUpdate_table { uint8_t unused__; };

static inline size_t getugo_VehicleTelemetryUpdate_vec_len(getugo_VehicleTelemetryUpdate_vec_t vec)
__flatbuffers_vec_len(vec)
static inline getugo_VehicleTelemetryUpdate_table_t getugo_VehicleTelemetryUpdate_vec_at(getugo_VehicleTelemetryUpdate_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(getugo_VehicleTelemetryUpdate_table_t, vec, i, 0)
__flatbuffers_table_as_root(getugo_VehicleTelemetryUpdate)

__flatbuffers_define_scalar_field(0, getugo_VehicleTelemetryUpdate, velocity, flatbuffers_float, float, 0.000000f)
__flatbuffers_define_scalar_field(1, getugo_VehicleTelemetryUpdate, actual_angle, flatbuffers_float, float, 0.000000f)
__flatbuffers_define_scalar_field(2, getugo_VehicleTelemetryUpdate, actual_angle_rear_axle, flatbuffers_float, float, 0.000000f)
typedef uint8_t getugo_Payload_union_type_t;
__flatbuffers_define_integer_type(getugo_Payload, getugo_Payload_union_type_t, 8)
__flatbuffers_define_union(flatbuffers_, getugo_Payload)
#define getugo_Payload_NONE ((getugo_Payload_union_type_t)UINT8_C(0))
#define getugo_Payload_VehicleControlRequest ((getugo_Payload_union_type_t)UINT8_C(1))
#define getugo_Payload_VehicleTelemetryUpdate ((getugo_Payload_union_type_t)UINT8_C(2))
#define getugo_Payload_CameraRequest ((getugo_Payload_union_type_t)UINT8_C(3))
#define getugo_Payload_Ping ((getugo_Payload_union_type_t)UINT8_C(4))
#define getugo_Payload_Pong ((getugo_Payload_union_type_t)UINT8_C(5))
#define getugo_Payload_EgoPose ((getugo_Payload_union_type_t)UINT8_C(6))

static inline const char *getugo_Payload_type_name(getugo_Payload_union_type_t type)
{
    switch (type) {
    case getugo_Payload_NONE: return "NONE";
    case getugo_Payload_VehicleControlRequest: return "VehicleControlRequest";
    case getugo_Payload_VehicleTelemetryUpdate: return "VehicleTelemetryUpdate";
    case getugo_Payload_CameraRequest: return "CameraRequest";
    case getugo_Payload_Ping: return "Ping";
    case getugo_Payload_Pong: return "Pong";
    case getugo_Payload_EgoPose: return "EgoPose";
    default: return "";
    }
}

static inline int getugo_Payload_is_known_type(getugo_Payload_union_type_t type)
{
    switch (type) {
    case getugo_Payload_NONE: return 1;
    case getugo_Payload_VehicleControlRequest: return 1;
    case getugo_Payload_VehicleTelemetryUpdate: return 1;
    case getugo_Payload_CameraRequest: return 1;
    case getugo_Payload_Ping: return 1;
    case getugo_Payload_Pong: return 1;
    case getugo_Payload_EgoPose: return 1;
    default: return 0;
    }
}


struct getugo_TeleopMsg_table { uint8_t unused__; };

static inline size_t getugo_TeleopMsg_vec_len(getugo_TeleopMsg_vec_t vec)
__flatbuffers_vec_len(vec)
static inline getugo_TeleopMsg_table_t getugo_TeleopMsg_vec_at(getugo_TeleopMsg_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(getugo_TeleopMsg_table_t, vec, i, 0)
__flatbuffers_table_as_root(getugo_TeleopMsg)

__flatbuffers_define_struct_field(0, getugo_TeleopMsg, teleop_header, getugo_Header_struct_t, 1)
__flatbuffers_define_union_field(flatbuffers_, 2, getugo_TeleopMsg, payload, getugo_Payload, 0)


#include "flatcc/flatcc_epilogue.h"
#endif /* TELEOP_CAR_READER_H */
