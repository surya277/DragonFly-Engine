#include "Object.h"
#include "WorldManager.h"
#include "DisplayManager.h"


#include <iostream>

namespace df {

	Object::Object() {
		static int id = 0;
		m_id = id++;
		m_type = "Object";

		m_speed = 0.0f;
		m_solidness = HARD;
		m_no_soft = false;
		m_altitude = 2;
		// Add self to WorldManager
		WM.insertObject(this);
	}

	void Object::setId(int new_id) {
		m_id = new_id;
	}
	
	int Object::getId() const {
		return m_id;
	}

	void Object::setType(std::string new_type) {
		m_type = new_type;
	}

	std::string Object::getType() const {
		return m_type;
	}

	void Object::setPosition(Vector new_pos) {
		m_position = new_pos;
	}

	Vector Object::getPosition() const {
		return m_position;
	}

	int Object::eventHandler(const Event* p_e)
	{
		//std::cout << p_e->getType();

		return 0;
	}

	// Draw Object
	int Object::draw() {
		char ch = '+';
		DM.drawCh(m_position,ch,df::RED);
		return 1;
	}

	// Set altitude of Object
	int Object::setAltitude(int new_altitude) {
		if (new_altitude >= 0 && new_altitude < MAX_ALTITUDE) {
			m_altitude = new_altitude;
			return 0;
		}
		return -1;

	}

	// Return Altitude of Object
	int Object::getAltitude() const {
		return m_altitude;
	}

	// Set direction of Object
	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction;
	}

	// Get direction of Object
	Vector Object::getDirection() const {
		return m_direction;
	}

	// Set speed of Object
	void Object::setSpeed(float speed) {
		m_speed = speed;
	}

	// Get speed of Object
	float Object::getSpeed() const {
		return m_speed;
	}

	// Set direction and speed of Object
	void Object::setVelocity(Vector new_velocity) {
		m_speed = new_velocity.getMagnitude();
		new_velocity.normalize();
		m_direction = new_velocity;
	}

	// Get Velocity of object based on speed and direction
	Vector Object::getVelocity() const {
		Vector vel = m_direction;
		vel.scale(m_speed);
		return vel;
	}

	// Predict Object position based on speed and direction
	// Return Predicted Position
	Vector Object::predictPosition() {
		Vector new_pos = m_position + getVelocity();
		return new_pos;
	}

	// True if solidness is Hard or soft, else false
	bool Object::isSolid() const {
		if (m_solidness == HARD || m_solidness == SOFT)
			return true;
		return false;
	}

	// Set Object Solidness
	int Object::setSolidness(Solidness new_solid) {
		if (new_solid < HARD || new_solid > SPECTRAL)
			return -1;
		m_solidness = new_solid;
		return 0;
	}

	// Get Object Solidness
	Solidness Object::getSolidness() const {
		return m_solidness;
	}

	// Set "no soft" setting (True - Cannot move onto SOFT Objects)
	void Object::setNoSoft(bool new_no_soft) {
		m_no_soft = new_no_soft;
	}

	// Get "no soft"
	bool Object::getNoSoft() const {
		return m_no_soft;
	}

	Object::~Object() {
		WM.removeObject(this);					//Remove Self from game world
	}

}