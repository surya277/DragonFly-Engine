#pragma once

#include "Event.h"

namespace df {

	const std::string KEYBOARD_EVENT = "df::keyboard";

	// Types of Keyboard Actions Dragonfly recognizes
	enum EventKeyboardAction {
		UNDEFINED_KEYBOARD_ACTION = -1,
		KEY_PRESSED,
		KEY_RELEASED,
		KEY_DOWN,
	};
	

	// Keys Dragonfly recognizes
	namespace Keyboard {
		enum key {
			UNDEFINED_KEY = -1,
			SPACE, RETURN, ESCAPE, TAB,
			LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW,
			PAUSE, MINUS, PLUS, TILDE, PERIOD, COMMA, SLASH, LEFTCONTROL, RIGHTCONTROL, LEFTSHIFT, RIGHTSHIFT,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0,
		};
	}

	class EventKeyboard : public Event
	{
	private:
		Keyboard::key m_key_val;
		EventKeyboardAction m_keyboard_action;

	public:
		EventKeyboard();

		// Set key in event
		void setKey(Keyboard::key new_key);

		// Get key from event
		Keyboard::key getKey() const;

		// Set Keyboard Action Event
		void setKeyboardAction(EventKeyboardAction new_action);

		// Get keyboard Action Event
		EventKeyboardAction getKeyboardAction() const;

	};


}

