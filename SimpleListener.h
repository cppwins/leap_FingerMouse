#ifndef _LISTENER_H_
#define _LISTENER_H_

#include <iostream>
#include "Leap.h"
#include "windows.h"

using namespace Leap;

// create a subclass of Leap::Listener
// implement the callback functions for events
class SimpleListener : public Listener {
public:
	virtual void onConnect(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onInit(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
};

#endif