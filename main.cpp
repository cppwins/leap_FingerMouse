#include <iostream>
#include "SimpleListener.h"

int main(int argc, char** argv) {
	// add a Leap::Controller object
	// add a subclass of Leap::Listener
	// add the listener to controller
	Controller controller;
	controller.setPolicyFlags(Controller::POLICY_BACKGROUND_FRAMES);
	SimpleListener listener;
	controller.addListener(listener);

	int width = GetSystemMetrics(0);
	int height = GetSystemMetrics(1);
	std::cout << "screen resolution: " << width << ", " << height << std::endl;

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	controller.removeListener(listener);
	return 0;
}