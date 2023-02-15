#include "EventStep.h"

namespace df {

	EventStep::EventStep() {
		setType(STEP_EVENT);
	}

	// Constructor with initial step count
	EventStep::EventStep(int init_step_count) {
		m_step_count = init_step_count;
		setType(STEP_EVENT);
	}


	// Set step count
	void EventStep::setStepCount(int new_step_count) {
		m_step_count = new_step_count;
	}


	// Get step count
	int EventStep::getStepCount() const {
		return m_step_count;
	}

}
