#ifndef Drone_h
#define Drone_h

#include "LeapMotion.h"

class Drone {
private:
    const int axis_z = 13;
    const int axis_y = 11;
    const int axis_x = 10;

    const int max = 255;
    const int default_axis_z = max;
    const int default_axis_y = max/2;
    const int defualt_axis_x = max/2;

    int convert(int n);

public:
    Drone();
    //void set_action(HandInfo handinfo);
    void sync();
    void setAction(HandInfo handinfo);
};

#endif
