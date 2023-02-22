#include "Vector.h"
#include<math.h>
namespace df {

	// Default Vector with (0,0)
	Vector::Vector() {
		m_x = 1.0f;
		m_y = 1.0f;
	}


	// Initialize Vector with x and y
	Vector::Vector(float init_x, float init_y) {
		m_x = init_x;
		m_y = init_y;
	}

	// Set X coordinate
	void Vector::setX(float new_x) {
		m_x = new_x;
	}

	// Get X coordinate
	float Vector::getX() const {
		return m_x;
	}

	// Set Y coordinate
	void Vector::setY(float new_y) {
		m_y = new_y;
	}

	// Get Y coordinate
	float Vector::getY() const {
		return m_y;
	}

	// Set X,Y Coordinate
	void Vector::setXY(float new_x, float new_y) {
		m_x = new_x;
		m_y = new_y;
	}

	// Return Magnitude of Vector
	float Vector::getMagnitude() const {
		return sqrt(m_x * m_x + m_y * m_y);
	}

	// Normalize Vector
	void Vector::normalize() {
		float magnitude = getMagnitude();
		if (magnitude > 0) {
			m_x = m_x / magnitude;
			m_y = m_y / magnitude;
		}
	}

	// Scale Vector
	void Vector::scale(float s) {
		m_x = m_x * s;
		m_y = m_y * s;
	}

	// Add 2 Vectors and return new Vector
	Vector Vector::operator+(const Vector& other) const {
		Vector v;
		v.m_x = m_x + other.m_x;
		v.m_y = m_y + other.m_y;
		return v;
	}

	// Subtract 2 Vectors and return new Vector
	Vector Vector::operator-(const Vector& other) const {
		Vector v;
		v.m_x = m_x - other.m_x;
		v.m_y = m_y - other.m_y;
		return v;
	}


	Vector& Vector::operator=(const Vector& v) {
		m_x = v.m_x;
		m_y = v.m_y;

		return *this;
	}



}
