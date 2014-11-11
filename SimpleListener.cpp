#include "SimpleListener.h"

void SimpleListener::onInit(const Controller& controller) {
	std::cout << "initialized" << std::cout;
}

void SimpleListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	//controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SimpleListener::onDisconnect(const Controller& controller) {
	std::cout << "Disconnected" << std::endl;
}

void SimpleListener::onExit(const Controller& controller) {
	std::cout << "Exit" << std::endl;
}


void SimpleListener::onFrame(const Controller& controller) {
	
	const Frame frame = controller.frame();

	if(frame.hands().count() > 0) {
		Hand hand = frame.hands().rightmost();
		FingerList fingers = hand.fingers();
		
		Finger index = hand.fingers().fingerType(Finger::TYPE_INDEX)[0];
		Finger middle = hand.fingers().fingerType(Finger::TYPE_MIDDLE)[0];
		Finger ring = hand.fingers().fingerType(Finger::TYPE_RING)[0];
		
		Vector indexPos = index.stabilizedTipPosition();
		InteractionBox iBox = frame.interactionBox();
		Vector cursorPos = iBox.normalizePoint(indexPos);
		int x = cursorPos.x * GetSystemMetrics(0);
		int y = GetSystemMetrics(1) - cursorPos.y * GetSystemMetrics(1);
		
		if(index.touchZone() == Pointable::Zone::ZONE_TOUCHING &&
			middle.touchZone() == Pointable::Zone::ZONE_TOUCHING &&
			ring.touchZone() == Pointable::Zone::ZONE_TOUCHING) {
			// mouse wheel
			float vel = index.tipVelocity().y;
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_WHEEL, 0, 0, vel * 0.1, 0);
		}
		else if(index.touchZone() == Pointable::Zone::ZONE_TOUCHING)				
			// left mouse key down
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		else if(index.touchZone() == Pointable::Zone::ZONE_TOUCHING && 
				middle.touchZone() == Pointable::Zone::ZONE_TOUCHING) {
				// right mouse key down
			Frame prevFrame = controller.frame(1);
			Finger prevMid = prevFrame.fingers().fingerType(Finger::TYPE_MIDDLE)[0];
			if(prevMid.touchZone() == Pointable::Zone::ZONE_HOVERING) {
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			}
		}
		else
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		std::cout << "  horizontal angel: " << index.direction().angleTo(Vector(0,0,-1.0)) * 180 / 3.1415926
				  << std::endl;
		

		SetCursorPos(x, y);
	}
	else
		std::cout << "No paws in sight!" << std::endl;
}