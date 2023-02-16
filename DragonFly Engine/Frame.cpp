#include "Frame.h"
#include "LogManager.h"
#include "DisplayManager.h"

namespace df {

	// Create empty frame
	Frame::Frame(){
		m_width = 0;
		m_height = 0;
	}

	// Create frame of indicated width and frame
	Frame::Frame(int new_width, int new_height, std::string frame_str){
		m_width = new_width;
		m_height = new_height;
		m_frame_str = frame_str;
	}

	// Set width of frame
	void Frame::setWidth(int new_width) {
		m_width = new_width;
	}

	// Get Width of frame
	int Frame::getWidth() const {
		return m_width;
	}


	// Set Height of frame
	void Frame::setHeight(int new_height) {
		m_height = new_height;
	}

	// Get height of frame
	int Frame::getHeight() const {
		return m_height;
	}

	// Set frame characters (stored as string)
	void Frame::setString(std::string new_frame_str) {
		m_frame_str = new_frame_str;
	}

	// Get frame characters (stored as string)
	std::string Frame::getString() const {
		return m_frame_str;
	}

	// Draw self, centered at position (x,y) with color/
	// Return 0 if ok, else -1.
	// Note: top-left, coordinate is (0,0)
	int Frame::draw(Vector position, Color color, char transparency) const{

		if (empty(m_frame_str)) {
			LM.writeLog("Empty Frame String");
			return -1;
		}

		int x_offset = getWidth() / 2;
		int y_offset = getHeight() / 2;

		// Draw character by character
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				if (transparency == 0 || m_frame_str[i * getWidth() + j]) {
					Vector temp_pos(position.getX() + j - x_offset, position.getY() + i - y_offset);
					DM.drawCh(temp_pos, m_frame_str[i * m_width + j], color);
				}

			}
		}

	}



}