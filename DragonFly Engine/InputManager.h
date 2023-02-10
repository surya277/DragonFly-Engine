#pragma once

#include "Manager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#define IM df::InputManager::getInstance()

namespace df {
	

	class InputManager : public Manager {

	private:
		InputManager();									// Private (A singleton)
		InputManager(InputManager& const);				// Don't Allow copy
		void operator=(InputManager& const);			// Don't allow assignment
	
	public:
		
		// Get the one and only instance of the InputManager
		static InputManager& getInstance();

		// Get window ready to capture input
		// Return 0 if ok, else -1
		int startUp();

		// Revert back to normal window mode
		void shutDown();

		// Get input from the keyboard and mouse
		// Pass event along to all Objects
		void getInput();

		// Return equivalent DF key code
		Keyboard::key getDfCode(int n);

		// Return equivalent df Mouse code
		Mouse::Button getDfMouseCode(int n);
	};


}

