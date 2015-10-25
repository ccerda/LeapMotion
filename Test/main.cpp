#include "Controls.h"
#include <iostream>
#include "Leap.h"

using namespace Leap;

int main(int argc, char* *argv){
    PROTOYPE_Listener listener;
    Controller controller;
    controller.addListener(listener);

    std::cout << "Complete" << std::endl;

    controller.removeListener(listener);
    return 0;
}
