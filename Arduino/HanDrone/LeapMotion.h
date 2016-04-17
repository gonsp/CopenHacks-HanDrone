#ifndef LeapMotion_h
#define LeapMotion_h

#include <Arduino.h>

struct HandInfo {
    int axis_x;
    int axis_y;
    int axis_z;
    int done = 0;
};

class LeapMotion {
private:
    char buffer[10];
    int i = 0;
    HandInfo handinfo;
public:
    LeapMotion();
    bool read();
    HandInfo getHandInfo() const;
};

#endif
