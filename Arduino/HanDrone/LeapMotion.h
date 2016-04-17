#ifndef LeapMotion_h
#define LeapMotion_h

#include <Arduino.h>

struct HandInfo {
    double axis_x;
    double axis_y;
    double axis_z;
    bool cercle;
};

class LeapMotion {
private:
    char buffer[30];
    HandInfo last_handinfo;
    char* readString();
public:
    LeapMotion();
    bool refresh();
    HandInfo getHandInfo() const;
};

#endif
