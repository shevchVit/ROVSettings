#ifndef PACKETS_H
#define PACKETS_H

#endif // PACKETS_H

#include <stdint.h>

struct InputPacket
{
    float Yaw = 0;
    float Pitch = 0;
    float Roll = 0;
    float Depth = 0;
};

struct OutputPacket
{
    bool isSettigsEnd = false;

    int8_t axis_X;
    int8_t axis_Y;
    int8_t axis_Z;
    int8_t axis_W;

    float YawKp;
    float YawKi;
    float YawKd;

    float PitchKp;
    float PitchKi;
    float PitchKd;

    float RollKp;
    float RollKi;
    float RollKd;

    float DepthKp;
    float DepthKi;
    float DepthKd;

    float YawToSet;
    float PitchToSet;
    float RollToSet;
    float DepthToSet;

    bool regulators[4];
};
