#pragma once

namespace df {

	class Vector
	{
	private:
		float m_x;
		float m_y;

	public:
		// Initialize Vector with x and y
		Vector(float init_x, float init_y);

		// Default Vector with (0,0)
		Vector();

		// Get/Set X coordinate
		void setX(float new_x);
		float getX() const;

		// Get/Set Y coordinate
		void setY(float new_y);
		float getY() const;

		// Set both X and Y
		void setXY(float new_x, float new_y);

		// Return Mangitude of vector
		float getMagnitude() const;

		// Normalize Vector
		void normalize();
		
		// Scale Vector
		void scale(float s);

		// Add two vector and return new Vector
		Vector operator+(const Vector& other) const;

		// Subtract two vector and return new Vector
		Vector operator-(const Vector& other) const;

		// Assignment
		Vector& operator=(const Vector& v);

		//Multiply vector with scalar, return new Vector
		// operator*(float s) const;
	};
}
