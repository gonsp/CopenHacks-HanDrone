#include "LeapMotion.h"

LeapMotion::LeapMotion() {
    Serial.begin(9600);
}

bool LeapMotion::refresh() {
    if(Serial.available()) {
        char buffer[30];
        int i = 0;
        while(i < 30 && Serial.available()) {
            buffer[i] = Serial.read();
            ++i;
            delay(10);
        }
        buffer[i-1] = '\0';
        //Serial.println(1);
        return true;
    } else {
        return false;
    }
}

double LeapMotion::string_to_double(char* s) {

}
