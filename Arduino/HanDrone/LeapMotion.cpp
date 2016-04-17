#include "LeapMotion.h"

LeapMotion::LeapMotion() {
}

bool LeapMotion::refresh() {
    if(Serial.available()) {
        last_handinfo.axis_x = atoi(readString());
        last_handinfo.axis_y = atoi(readString());
        last_handinfo.axis_z = atoi(readString());
        last_handinfo.cercle = atoi(readString()) == 1;
        return true;
    } else {
        return false;
    }
}

char* LeapMotion::readString() {
    int i = 0;
    while(i < 30 && Serial.available()) {
        buffer[i] = Serial.read();
        ++i;
        delay(10);
    }
    return buffer;
}

HandInfo LeapMotion::getHandInfo() const {
    return last_handinfo;
}
