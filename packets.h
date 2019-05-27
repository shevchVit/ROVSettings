#ifndef PACKETS_H
#define PACKETS_H

#endif // PACKETS_H

#include <stdint.h>

struct InputPacket
{
    float yaw = 0;
    float roll = 0;
    float pitch = 0;
    float depth = 0;
    float temperature = 0;
    uint8_t core = 0;
};

#pragma pack(push,1)
struct OutputPacket
{
    bool is_settings = true;

    int8_t axis_X = 0;
    int8_t axis_Y = 0;
    int8_t axis_Z = 0;
    int8_t axis_W = 0;

    float YawKp = 0;
    float YawKi = 0;
    float YawKd = 0;

    float PitchKp = 0;
    float PitchKi = 0;
    float PitchKd = 0;

    float RollKp = 0;
    float RollKi = 0;
    float RollKd = 0;

    float DepthKp = 0;
    float DepthKi = 0;
    float DepthKd = 0;

    uint16_t YawToSet = 0;
    uint16_t PitchToSet = 0;
    uint16_t RollToSet = 0;
    uint16_t DepthToSet = 0;

    uint8_t yaw_regulator = 0;
    uint8_t pitch_regulator = 0;
    uint8_t roll_regulator = 0;
    uint8_t depth_regulator = 0;

};
#pragma pack(pop)
