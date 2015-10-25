#include <string.h>
#include <iostream>
#include "Leap.h"

using namespace Leap;

class PROTOYPE_Listener: public Listener {
public:
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onFrame(const Controller&);
};

