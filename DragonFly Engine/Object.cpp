#include "Object.h"
#include "WorldManager.h"
#include "DisplayManager.h"

namespace df {

	Object::Object() {
		static int id = 0;
		m_id = id++;
		m_type = "Object";

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
		return 0;
	}

	// Draw Object
	int Object::draw() {
		//DM.drawCh(m_position, );
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


	Object::~Object() {
		WM.removeObject(this);					//Remove Self from game world
	}

}