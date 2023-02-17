#include "Box.h"


namespace df {

	// Create Box with (0,0) for the corner, and 0 for horiz and vertical
	Box::Box() {
		m_corner = Vector(0, 0);
		m_horizontal = 0.0f;
		m_vertical = 0.0f;
	}

	// Create Box with an upper left corner, horizontal and vertical sizes
	Box::Box(Vector init_corner, float init_horizontal, float init_vertical) {
		m_corner = init_corner;
		m_horizontal = init_horizontal;
		m_vertical = init_vertical;
	}

	// Set upper left corner of box
	void Box::setCorner(Vector new_corner) {
		m_corner = new_corner;
	}

	// Get upper left corner of box
	Vector Box::getCorner() const {
		return m_corner;
	}

	// Set horizontal size of box
	void Box::setHorizontal(float new_horizontal) {
		m_horizontal = new_horizontal;
	}

	// Get horizontal size of box
	float Box::getHorizontal() const {
		return m_horizontal;
	}

	// Set Vertical size of box
	void Box::setVertical(float new_vertical) {
		m_vertical = new_vertical;
	}

	//  Get Vertical size of box
	float Box::getVertical() const {
		return m_vertical;
	}


}