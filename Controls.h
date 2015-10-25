#include <string>
#include <iostream>
#include <fstream>
#include "../LeapSDK/include/Leap.h"
using namespace Leap;

class getData_listener : public Listener {
    public:
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onFrame(const Controller&);
};


