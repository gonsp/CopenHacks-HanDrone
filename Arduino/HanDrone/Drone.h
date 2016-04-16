#ifndef Drone_h
#define Drone_h

#define axis_z A3
#define axis_y A0
#define axis_x A1

#define max 755

#define default_axis_z max
#define default_axis_y max/2
#define default_axis_x max/2

class Drone {
private:
public:
    Drone();
    void set_action(HandInfo handinfo);

};

#endif
