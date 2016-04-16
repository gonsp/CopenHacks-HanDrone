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
	double direction;
	double power;
	double turn;

};

void SampleListener::onConnect(const Controller& controller) {
    cout << "Connected" << endl;
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
	if (frame.id() % 20 == 0) {
		/*
		cout
			<< "Frame id: " << frame.id()
        	<< ", timestamp: " << frame.timestamp()
        	<< ", hands: " << frame.hands().count()
        	<< ", fingers: " << frame.fingers().count()
        	<< ", tools: " << frame.tools().count()
        	<< ", gestures: " << frame.gestures().count() << endl;
        	//*/

        Leap::Hand hand = frame.hands().leftmost();

        direction = hand.palmNormal()[2];
        power = hand.palmPosition()[1];
        turn = hand.palmNormal()[0];

        //cout <<hand.palmPosition()[1] <<endl;
        cout <<direction <<endl <<power <<endl <<turn <<endl <<endl;
	}
}

int main(int argc, char** argv) {
	SampleListener listener;
	Controller controller;

	controller.addListener(listener);

    //while(not controller.isConnected());

    //cout << "Connected!" <<endl;




    // Keep this process running until Enter is pressed
    cout << "Press Enter to quit..." << endl;
    cin.get();

    controller.removeListener(listener);

    return 0;
}