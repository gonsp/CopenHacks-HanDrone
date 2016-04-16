#include "Drone.h"
#include "LeapMotion.h"

Drone::Drone() {
    Serial.println("Drone sync starts");
    analogWrite(axis_z, default_axis_z);
    delay(500);
    analogWrite(axis_z, 0);
    delay(500);
    analogWrite(axis_z, default_axis_z);
    Serial.println("Drone sync finishes");
}

void Drone::setAction(HandInfo handinfo) {

}


