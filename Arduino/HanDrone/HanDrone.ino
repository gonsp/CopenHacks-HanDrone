#include "Drone.h"
#include "LeapMotion.h"

LeapMotion lm;
Drone drone;

void setup() {
    Serial.begin(9600);

    int eraser = 7;
    int prescaler = 1;
    TCCR0B &= ~eraser;
    TCCR0B |= prescaler;
    TCCR1B &= ~eraser;
    TCCR1B |= prescaler;
    TCCR2B &= ~eraser;
    TCCR2B |= prescaler;

    drone.sync();
}

void loop() {
    if(lm.read()) {
        drone.setAction(lm.getHandInfo());
    }
}
