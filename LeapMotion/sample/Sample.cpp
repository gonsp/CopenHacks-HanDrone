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
    double power; // axis_z
    //double powerMax; // 400 // 350
    //double powerMin; // 50  // 100
    double direction; // axis_y
    //double directionMax; // 0.8
    //double directionMin; // 1
    double turn; // axis_x
    //double turnMax; // 1
    //double turnMin; // 1

};

void SampleListener::onConnect(const Controller& controller) {
    cout << "Connected" << endl;
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.config().setFloat("Gesture.Circle.MinRadius", 100.0);
    controller.config().save();


}

void SampleListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    bool circle = false;

    Leap::GestureList gestures = frame.gestures();
    for(Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); gl++) {
        if ((*gl).type() == Leap::Gesture::TYPE_CIRCLE) {
            circle = true;
        }
    }

    Leap::Hand hand = frame.hands().leftmost();

    power = hand.palmPosition()[1];
    direction = hand.palmNormal()[2];
    turn = hand.palmNormal()[0];

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