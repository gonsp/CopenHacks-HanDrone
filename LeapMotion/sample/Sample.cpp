//#include <iostream>
#include <std::string.h>
#include "Leap.h"

#include <stdio.h> // standard input / output functions
#include <std::string.h> // std::string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls

using namespace Leap;
//using namespace std;

int fd;

//////////////////////////////// LEAP ////////////////////////////////

class SampleListener : public Listener {

public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);

private:
    double power; // axis_z
    //double powerMax; // 400 // 350
    //double powerMin; // 50  // 100
    double direction; // axis_y
    //double directionMax; // -0.8
    //double directionMin; // 1
    double turn; // axis_x
    //double turnMax; // -1
    //double turnMin; // 1


};

void SampleListener::onConnect(const Controller& controller) {
    //cout << "Connected" << endl;
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.config().setFloat("Gesture.Circle.MinRadius", 100.0);
    controller.config().save();

}

void SampleListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    std::string circle = "0";

    Leap::GestureList gestures = frame.gestures();
    for(Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); gl++) {
        if ((*gl).type() == Leap::Gesture::TYPE_CIRCLE) {
            circle = "1";
        }
    }

    Leap::Hand hand = frame.hands().leftmost();

    power = hand.palmPosition()[1];
    int powerInt = (int) (power * 100);
    std::string powerStr = to_std::string(powerInt);

    direction = hand.palmNormal()[2];
    int directionInt = (int) (direction * 100);
    std::string directionStr = to_std::string(directionInt);

    turn = hand.palmNormal()[0];
    int turnInt = (int) (turn * 100);
    std::string turnStr = to_std::string(turnInt);

    write(fd, turnStr, turnStr.size());
    write(fd, directionStr, directionStr.size());
    write(fd, powerInt, powerInt.size());
    write(fd, circle, circle.size());

}

//////////////////////////////// PORT ////////////////////////////////

int open_port(void)
{
    //int fd; // file description for the serial port

    fd = open("/dev/ttyACM0", O_RDWR );
    //fd = open("salida.txt", O_RDWR | O_NOCTTY | O_NDELAY);

    if(fd == -1) // if open is unsucessful
    {
        //perror("open_port: Unable to open /dev/ttyUSB0 - ");
        printf("open_port: Unable to open /dev/ttyACM0. \n");
    }
    else
    {
        fcntl(fd, F_SETFL, 0);
        printf("port is open.\n");
    }

    return(fd);
}

int configure_port()      // configure the port
{
    struct termios port_settings;      // structure to store the port settings in

    cfsetispeed(&port_settings, B115200);    // set baud rates
    cfsetospeed(&port_settings, B115200);

    port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
    port_settings.c_cflag &= ~CSTOPB;
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;

    tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port
    return(fd);

}

//////////////////////////////// MAIN ////////////////////////////////

int main(int argc, char** argv) {

    // PORT
    fd = open_port();
    configure_port();



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