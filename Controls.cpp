#include "Controls.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include "../LeapSDK/include/Leap.h"

using namespace Leap;
 
void getData_listener::onConnect(const Controller& controller){
    controller.enableGesture(Gesture::TYPE_SWIPE);
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
}

void getData_listener::onDisconnect(const Controller& controller){
    std::cout << "Listener is disconnected" << std::endl;
}

void getData_listener::onFrame(const Controller& controller){
    std::string outFilename = "Test2";
    std::fstream out(outFilename, std::ios_base::app | std::ios_base::out);
    if(out)
    {
        for (int f = 1; f >= 0; f--) { 
            Frame frameToSerialize = controller.frame(f);
            if (frameToSerialize.hands().count()){
                std::string serialized = frameToSerialize.serialize();
                out << (long)serialized.length() << serialized;
                std::cout << frameToSerialize.hands().rightmost().palmVelocity() << std::endl;
                std::cout << frameToSerialize.hands().leftmost().palmVelocity() << std::endl;
                std::cout << std::endl;
            }

        }
        out.flush();
        out.close();
    }
    else if(errno) {
        std::cout << "Error: " << errno << std::endl;
        std::cout << "Couldn't open " << outFilename << " for writing." << std::endl;
    }
    usleep(100);
}

