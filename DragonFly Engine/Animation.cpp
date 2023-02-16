#include "Animation.h"
#include "LogManager.h"

namespace df {
	// Animation Constructor
	Animation::Animation() {
		m_index = 0;
		m_slowdown_count = 0;
	}

	// Set Associated sprite to new one.
	// Note, Sprite is managed by ResourceManager
	// Set sprite index to 0 (First Frame)
	void Animation::setSprite(Sprite* p_new_sprite) {
		m_p_sprite = p_new_sprite;
	}

	// Return pointer to associated sprite
	Sprite* Animation::getSprite() const {
		return m_p_sprite;
	}


	// Set sprite name (in Resource Manager)
	void Animation::setName(std::string new_name) {
		m_name = new_name;
	}

	// Get sprite name (in Resource Manager)
	std::string Animation::getName() const {
		return m_name;
	}

	// set index of current sprite frame to be displayed
	void Animation::setIndex(int new_index) {
		m_index = new_index;
	}

	// Get index of current sprite frame to be displayed
	int Animation::getIndex() const {
		return m_index;
	}

	// Set animation slowdown count (-1 means stop animation)
	void Animation::setSlowdownCount(int new_slowdown_count) {
		m_slowdown_count = new_slowdown_count;
	}

	// Set animation slowdown count (-1 means stop animation)
	int Animation::getSlowdownCount() const {
		return m_slowdown_count;
	}

	// Draw single frame centered at position (x,y)
	// Drawing accounts for slowdown, and advances sprite frame
	// Return 0 if ok, else -1
	int Animation::draw(Vector position) {

		// If sprite not defined, don't continue further
		if (m_p_sprite == NULL) {
			LM.writeLog("Sprite not defined");
			return -1;
		}

		// Ask Sprite to draw current frame
		int index = getIndex();
		m_p_sprite->draw(index, position);

		// if slowdown count is -1, then animation is frozen
		if (getSlowdownCount() == -1)
			return 0;

		// Increment counter
		int count = getSlowdownCount();
		count++;

		if (count >= getSlowdownCount()) {
			count = 0;
			index++;							// Advance frame

			// if last frame loop to beginning
			if (index >= m_p_sprite->getFrameCount()) {
				index = 0;
			}
			// set index for next draw()
			setIndex(index);
		}

		// Set counter for next draw()
		setSlowdownCount(count);

	}



}