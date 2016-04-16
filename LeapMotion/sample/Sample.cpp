#include <iostream>
#include <string.h>
#include "Leap.h"

using namespace Leap;
using namespace std;

class SampleListener : public Listener {

public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);

private:
    double direction; // axis_y
    double power; // axis_z
    double turn; // axis_x

};

void SampleListener::onConnect(const Controller& controller) {
    cout << "Connected" << endl;
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.config().setFloat("Gesture.Circle.MinRadius", 10.0);
    controller.config().save();
}

void SampleListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    if (frame.gestures().count() > 0) {

    }

    Leap::Hand hand = frame.hands().leftmost();

    direction = hand.palmNormal()[2];
    power = hand.palmPosition()[1];
    turn = hand.palmNormal()[0];

    cout <<direction <<endl <<power <<endl <<turn <<endl <<endl;


}

int main(int argc, char** argv) {
    SampleListener listener;
    Controller controller;

    controller.addListener(listener);

    // Keep this process running until Enter is pressed
    cout << "Press Enter to quit..." << endl;
    cin.get();

    controller.removeListener(listener);

    return 0;
}