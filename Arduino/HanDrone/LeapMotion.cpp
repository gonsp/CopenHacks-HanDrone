#include "LeapMotion.h"

LeapMotion::LeapMotion() {
}

bool LeapMotion::read() {
    if(Serial.available()) {
        char c = Serial.read();
        if(c == '-') {
            buffer[i] = '\0';
            if(handinfo.done == 0) {
                handinfo.axis_x = atoi(buffer);
            } else if(handinfo.done == 1) {
                handinfo.axis_y = atoi(buffer);
            } else {
                handinfo.axis_z = atoi(buffer);
            }
            ++handinfo.done;
            i = 0;
        } else {
            buffer[i] = c;
            ++i;
        }
    }
    if(handinfo.done == 3) {
        handinfo.done = 0;
        return true;
    } else {
        return false;
    }
}

HandInfo LeapMotion::getHandInfo() const {
    return handinfo;
}
