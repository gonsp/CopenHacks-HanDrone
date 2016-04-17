#include "Drone.h"
#include "LeapMotion.h"

Drone::Drone() {
}

void Drone::setAction(HandInfo handinfo) {
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

