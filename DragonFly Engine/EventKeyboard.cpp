#include "EventKeyboard.h"

namespace df {

	EventKeyboard::EventKeyboard() {
		m_key_val = Keyboard::UNDEFINED_KEY;
		m_keyboard_action = UNDEFINED_KEYBOARD_ACTION;
		setType(KEYBOARD_EVENT);
	}

	// Set key in event
	void EventKeyboard::setKey(Keyboard::key new_key) {
		m_key_val = new_key;
	}
	
	// Get Key from event
	Keyboard::key EventKeyboard::getKey() const {
		return m_key_val;
	}

	// Set keyboard Action Event
	void EventKeyboard::setKeyboardAction(EventKeyboardAction new_action) {
		m_keyboard_action = new_action;
	}

	// Get Keyboard Action event
	EventKeyboardAction EventKeyboard::getKeyboardAction() const{
		return m_keyboard_action;
	}
}