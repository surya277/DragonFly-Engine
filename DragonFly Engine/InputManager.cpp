#include "InputManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include <iostream>
namespace df {

	InputManager::InputManager() {
		

	}

	// Get one and only instance of the InputManager
	InputManager& InputManager::getInstance() {
		static InputManager InputManagerSingle;
		return InputManagerSingle;
	}

	// Get Window ready to capture input
	// Return 0 if ok else -1
	int InputManager::startUp() {
		if (Manager::isStarted())
			LM.writeLog("Input Manager has already been started\n");
		if (!DM.isStarted())
			return -1;
		sf::RenderWindow* window = DM.getWindow();

		window->setKeyRepeatEnabled(false);				// Disable Key repeating
		Manager::startUp();
		return 0;
	}
	
	// Revert Back to normal window
	void InputManager::shutDown() {
		sf::RenderWindow* window = DM.getWindow();
		window->setKeyRepeatEnabled(true);
		Manager::shutDown();
	}

	// Get Input from Keyboard and mouse
	// pass event along to all Objects
	void InputManager::getInput() {
		sf::RenderWindow* window = DM.getWindow();
		sf::Event event;
		
		// Check Past window inputs
		while (window->pollEvent(event)) {
			
			// Check if keypressed and send event
			if (event.type == sf::Event::KeyPressed){
				EventKeyboard keyboard_event;
				keyboard_event.setKey(getDfCode(event.key.code));
				keyboard_event.setKeyboardAction(df::KEY_PRESSED);
				onEvent(&keyboard_event);
			}

			// Check if key realeased and send event
			else if (event.type == sf::Event::KeyReleased){
				EventKeyboard keyboard_event;
				keyboard_event.setKey(getDfCode(event.key.code));
				keyboard_event.setKeyboardAction(df::KEY_RELEASED);
				onEvent(&keyboard_event);
			}
			// Check if mouse pressed and send event
			else if(event.type == sf::Event::MouseButtonPressed){
				EventMouse mouse_event;
				mouse_event.setMouseButton(getDfMouseCode(event.mouseButton.button));
				mouse_event.setMouseAction(df::CLICKED);
				mouse_event.setMousePosition(Vector(event.mouseButton.x / DM.charWidth(), event.mouseButton.y / DM.charHeight()));
				onEvent(&mouse_event);
			}

			// Check if mouse moved and send event
			else if (event.type == sf::Event::MouseMoved)
			{
				EventMouse mouse_event;
				//mouse_event.setMouseButton(getDfMouseCode(event.key.code));
				mouse_event.setMouseAction(df::MOVED);
				mouse_event.setMousePosition(Vector(event.mouseMove.x / DM.charWidth(), event.mouseMove.y / DM.charHeight()));
				onEvent(&mouse_event);
			}
		 }

		// Check live Input
		// Check if any DF Recognized key is pressed
		if (sf::Event::KeyPressed) {
			for (int i = 0; i != Keyboard::NUM0; i++) {
				if (event.key.code == (Keyboard::key)i) {
					EventKeyboard keyboard_event;
					keyboard_event.setKeyboardAction(df::KEY_PRESSED);
					onEvent(&keyboard_event);
				}
			}
		}

		// Check if any Df recognized Mouse button is pressed
		if (sf::Event::MouseButtonPressed) {
			for (int i = 0; i != Mouse::MIDDLE; i++) {
				if (event.mouseButton.button == (Mouse::Button)i) {
					EventMouse mouse_event;
					mouse_event.setMouseButton((Mouse::Button)i);
					mouse_event.setMouseAction(df::PRESSED);
					mouse_event.setMousePosition(Vector(event.mouseButton.x / DM.charWidth(), event.mouseButton.y / DM.charHeight()));
					onEvent(&mouse_event);
				}
			}
		}
	}

	Mouse::Button InputManager::getDfMouseCode(int n) {
		switch (n) {
		case sf::Mouse::Left:
			return Mouse::LEFT;
		case sf::Mouse::Right:
			return Mouse::RIGHT;
		case sf::Mouse::Middle:
			return Mouse::MIDDLE;
		}
		return Mouse::UNDEFINED_MOUSE_BUTTON;
	}

	Keyboard::key InputManager::getDfCode(int n) {
		switch (n) {
		case sf::Keyboard::A:
			return Keyboard::A;
		case sf::Keyboard::B:
			return Keyboard::B;
		case sf::Keyboard::C:
			return Keyboard::C;
		case sf::Keyboard::D:
			return Keyboard::D;
		case sf::Keyboard::E:
			return Keyboard::E;
		case sf::Keyboard::F:
			return Keyboard::F;
		case sf::Keyboard::G:
			return Keyboard::G;
		case sf::Keyboard::H:
			return Keyboard::H;
		case sf::Keyboard::I:
			return Keyboard::I;
		case sf::Keyboard::J:
			return Keyboard::J;
		case sf::Keyboard::K:
			return Keyboard::K;
		case sf::Keyboard::L:
			return Keyboard::L;
		case sf::Keyboard::M:
			return Keyboard::M;
		case sf::Keyboard::N:
			return Keyboard::O;
		case sf::Keyboard::P:
			return Keyboard::P;
		case sf::Keyboard::Q:
			return Keyboard::Q;
		case sf::Keyboard::R:
			return Keyboard::R;
		case sf::Keyboard::S:
			return Keyboard::S;
		case sf::Keyboard::T:
			return Keyboard::T;
		case sf::Keyboard::U:
			return Keyboard::U;
		case sf::Keyboard::V:
			return Keyboard::V;
		case sf::Keyboard::W:
			return Keyboard::W;
		case sf::Keyboard::X:
			return Keyboard::X;
		case sf::Keyboard::Y:
			return Keyboard::Y;
		case sf::Keyboard::Z:
			return Keyboard::Z;
		case sf::Keyboard::Space:
			return Keyboard::SPACE;
		case sf::Keyboard::Return:
			return Keyboard::RETURN;
		case sf::Keyboard::Escape:
			return Keyboard::ESCAPE;
		case sf::Keyboard::Tab:
			return Keyboard::TAB;
		case sf::Keyboard::Left:
			return Keyboard::LEFTARROW;
		case sf::Keyboard::Right:
			return Keyboard::RIGHTARROW;
		case sf::Keyboard::Up:
			return Keyboard::UPARROW;
		case sf::Keyboard::Down:
			return Keyboard::DOWNARROW;
		case sf::Keyboard::Pause:
			return Keyboard::PAUSE;
		case sf::Keyboard::Dash:
			return Keyboard::MINUS;
		case sf::Keyboard::Add:
			return Keyboard::PLUS;
		case sf::Keyboard::Tilde:
			return Keyboard::TILDE;
		case sf::Keyboard::Period:
			return Keyboard::PERIOD;
		case sf::Keyboard::Comma:
			return Keyboard::COMMA;
		case sf::Keyboard::Slash:
			return Keyboard::SLASH;
		case sf::Keyboard::LControl:
			return Keyboard::LEFTCONTROL;
		case sf::Keyboard::RControl:
			return Keyboard::RIGHTCONTROL;
		case sf::Keyboard::LShift:
			return Keyboard::LEFTSHIFT;
		case sf::Keyboard::RShift:
			return Keyboard::RIGHTSHIFT;
		case sf::Keyboard::F1:
			return Keyboard::F1;
		case sf::Keyboard::F2:
			return Keyboard::F3;
		case sf::Keyboard::F4:
			return Keyboard::F4;
		case sf::Keyboard::F5:
			return Keyboard::F5;
		case sf::Keyboard::F6:
			return Keyboard::F6;
		case sf::Keyboard::F7:
			return Keyboard::F7;
		case sf::Keyboard::F8:
			return Keyboard::F8;
		case sf::Keyboard::F9:
			return Keyboard::F9;
		case sf::Keyboard::F10:
			return Keyboard::F10;
		case sf::Keyboard::F11:
			return Keyboard::F11;
		case sf::Keyboard::F12:
			return Keyboard::F12;
		case sf::Keyboard::Num0:
			return Keyboard::NUM0;
		case sf::Keyboard::Num1:
			return Keyboard::NUM1;
		case sf::Keyboard::Num2:
			return Keyboard::NUM2;
		case sf::Keyboard::Num3:
			return Keyboard::NUM3;
		case sf::Keyboard::Num4:
			return Keyboard::NUM4;
		case sf::Keyboard::Num5:
			return Keyboard::NUM5;
		case sf::Keyboard::Num6:
			return Keyboard::NUM6;
		case sf::Keyboard::Num7:
			return Keyboard::NUM7;
		case sf::Keyboard::Num8:
			return Keyboard::NUM8;
		case sf::Keyboard::Num9:
			return Keyboard::NUM9;
		}
		return Keyboard::UNDEFINED_KEY;
	}





}