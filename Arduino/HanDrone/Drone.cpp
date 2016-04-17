#include "Drone.h"
#include "LeapMotion.h"

Drone::Drone() {
}

void Drone::setAction(HandInfo handinfo) {
    analogWrite(axis_x, handinfo.axis_x);
    analogWrite(axis_y, handinfo.axis_y);
    Serial.println(handinfo.axis_z);
    analogWrite(axis_z, handinfo.axis_z);
}

void Drone::sync() {
    analogWrite(axis_z, default_axis_z);
    Serial.println("Drone sync prepared, turn on the drone");
    delay(100000);
    Serial.println("Drone sync starts");
    analogWrite(axis_z, default_axis_z);
    delay(100000);
    analogWrite(axis_z, 0);
    delay(100000);
    analogWrite(axis_z, default_axis_z);
    Serial.println("Drone sync finishes");
}

