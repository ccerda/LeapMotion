#include "Controls.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Leap.h"

using namespace Leap;

void PROTOYPE_Listener::onConnect(const Controller& controller){
    std::cout << "Listener is connected" << std::endl;
}

void PROTOYPE_Listener::onDisconnect(const Controller& controller){
    std::cout << "Listener is disconnected" << std::endl;
}

void PROTOYPE_Listener::onFrame(const Controller& controller){
    const Frame frame = controller.frame();
    std::ofstream outputFile("frame.data");
    const std::string serializedFrame = frame.serialize();
    outputFile << serializedFrame;
    outputFile.close();
    std::cout << "Frame" << std::endl;
}
