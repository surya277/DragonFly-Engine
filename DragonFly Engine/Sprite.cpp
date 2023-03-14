#include "Sprite.h"
#include "LogManager.h"
#include "Frame.h"

namespace df {

	Sprite::Sprite() {
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_frame = new Frame;
		m_max_frame_count = 0;
		m_color = COLOR_DEFAULT;
		m_transparency = 0;
		m_slowdown = 1;
	}

	// Create sprite with indicated maximum number of frames
	Sprite::Sprite(int max_frame) {
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_frame = new Frame[max_frame];
		m_max_frame_count = max_frame;
		if (!m_frame) {
			LM.writeLog("Memory cannot be allocated for frame\n");
			max_frame = 0;
		}
		m_color = COLOR_DEFAULT;
		m_transparency = 0;
	}



	// Set width of frame
	void Sprite::setWidth(int new_width) {
		m_width = new_width;
	}

	// Get Width of frame
	int Sprite::getWidth() const {
		return m_width;
	}

	// Set Height of frame
	void Sprite::setHeight(int new_height) {
		m_height = new_height;
	}

	// Get height of frame
	int Sprite::getHeight() const {
		return m_height;
	}

	// Set Color of frame
	void Sprite::setColor(Color new_color) {
		m_color = new_color;
	}

	// Get Color of frame
	Color Sprite::getColor() const {
		return m_color;
	}

	// Get total count of frames in sprite
	int Sprite::getFrameCount() const {
		return m_frame_count;
	}

	// Set label associated with sprite
	void Sprite::setLabel(std::string new_label) {
		m_label = new_label;
	}

	// Get label associated with sprite
	std::string Sprite::getLabel() const {
		return m_label;
	}

	// Set animation slowdown value
	// Value in multiples of GameManager frame time
	void Sprite::setSlowdown(int new_sprite_slowdown) {
		m_slowdown = new_sprite_slowdown;
	}

	// Get animation slowdown value
	// Value in multiples of GameManager frame time
	int Sprite::getSlowdown() const {
		return m_slowdown;
	}


	// Set Sprite transparency character (0 means none)
	void Sprite::setTransparency(char new_transparency){
		m_transparency = new_transparency;
	}

	// Get Sprite transparency character (0 means none)
	char Sprite::getTransparency() const {
		return m_transparency;
	}



	// Add frame to sprite
	// Return -1 if frame array full, else 0
	int Sprite::addFrame(Frame new_frame) {
		// Check if frame array is filled
		if (m_frame_count > m_max_frame_count) {
			LM.writeLog("Sprite is Full\n");
			return -1;
		}
		else {
			m_frame[m_frame_count] = new_frame;
			m_frame_count++;
		}

	}

	// Get next sprite frame indicated by number
	Frame Sprite::getFrame(int frame_number) const {
		if ((frame_number < 0) || (frame_number >= m_frame_count)) {
			Frame empty;
			return empty;
		}
		return m_frame[frame_number];
	}

	int Sprite::draw(int frame_number, Vector position) const
	{
		if(frame_number >= 0 && frame_number < m_frame_count )
			return m_frame[frame_number].draw(position, m_color, m_transparency);

		return -1;
	}


	// Destroy sprite ,deleting any allocated frames .
	Sprite::~Sprite() {
		if (m_frame != NULL)
			delete[] m_frame;
	}
}