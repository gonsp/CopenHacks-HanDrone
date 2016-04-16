#ifndef LeapMotion_h
#define LeapMotion_h

struct HandInfo {
    double axis_x;
    double axis_y;
    double axis_z;
};

class LeapMotion {
private:
    HandInfo last_handinfo;
public:
    LeapMotion();
    bool refresh();
    HandInfo getHandInfo();
};

#endif
