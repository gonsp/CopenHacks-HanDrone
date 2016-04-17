#include <iostream>
#include <string.h>
#include "Leap.h"

#include <cstdio> // standard input / output functions
//#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <fstream>

using namespace Leap;
using namespace std;

int prescaler = 0;

//////////////////////////////// LEAP ////////////////////////////////

class SampleListener : public Listener {

public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);

private:

};

void SampleListener::onConnect(const Controller& controller) {
    cout << "Connected" << endl;
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.config().setFloat("Gesture.Circle.MinRadius", 100.0);
    controller.config().save();

}

void sendToArduino(int num) {
    FILE *file;
    file = fopen("/dev/ttyACM0", "w");
    fprintf(file, "%d-", num); //Writing to the file
    fclose(file);
    file = fopen("/dev/ttyACM1", "w");
    fprintf(file, "%d-", num); //Writing to the file
    fclose(file);
}

void SampleListener::onFrame(const Controller& controller) {

    const Frame frame = controller.frame();

    if(prescaler >= 10) {
        string circle = "0";

        Leap::GestureList gestures = frame.gestures();
        for(Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); gl++) {
            if ((*gl).type() == Leap::Gesture::TYPE_CIRCLE) {
                circle = "1";
            }
        }

        Leap::Hand hand = frame.hands().leftmost();

        double axis_x = hand.palmNormal()[0];
        double axis_y = hand.palmNormal()[2];
        double axis_z = hand.palmPosition()[1];

        if(axis_x != 0 || axis_y != 0 || axis_z != 0) {
            axis_x = axis_x*128 + 127;
            cout << axis_x << endl;
            sendToArduino((int)axis_x);

            axis_y = axis_y*128 + 127;
            cout << axis_y << endl;
            sendToArduino((int)axis_y);

            if(axis_z > 80) {
                axis_z = axis_z-80;
            } else {
                axis_z = 0;
            }
            if(axis_z > 255) {
                axis_z = 255;
            }
            cout << axis_z << endl;
            sendToArduino((int)axis_z);

            cout << "--------" << endl;
        } else {
            sendToArduino(255);
            sendToArduino(255);
            sendToArduino(255);
        }

        prescaler = 0;
    }
    ++prescaler;
}

//////////////////////////////// MAIN ////////////////////////////////

int main(int argc, char** argv) {

    // LEAP
    SampleListener listener;
    Controller controller;

    controller.addListener(listener);

    // Keep this process running until Enter is pressed
    //cout << "Press Enter to quit..." << endl;
    cin.get();

    controller.removeListener(listener);

    return 0;
}

