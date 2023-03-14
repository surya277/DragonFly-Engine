#include "EventView.h"

namespace df {

	// Create view event with tag VIEWEVENT, value 0 and delta false
	EventView::EventView() {
		setType(VIEW_EVENT);
		m_value = 0;
		m_delta = false;
		m_tag = "";

	}

	// Create view event with tag, value and delta as indicated
	EventView::EventView(std::string new_tag, int new_value, bool new_delta) {
		m_tag = new_tag;
		setType(VIEW_EVENT);
		m_value = new_value;
		m_delta = new_delta;
		
	}

	// Set tag to new tag
	void EventView::setTag(std::string new_tag) {
		m_tag = new_tag;
	}

	// Get tag
	std::string EventView::getTag() const {
		return m_tag;
	}

	// Set Value to new value
	void EventView::setValue(int new_value) {
		m_value = new_value;
	}

	// Get tag
	int EventView::getValue() const {
		return m_value;
	}

	// Set delta to new delta
	void EventView::setDelta(bool new_delta) {
		m_delta = new_delta;
	}

	// Get delta
	bool EventView::getDelta() const {
		return m_delta;
	}


}