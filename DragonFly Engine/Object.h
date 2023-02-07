#pragma once

#include <string>

#include "Vector.h"
#include "Event.h"
namespace df {


	class Object
	{
	private:
		int m_id;						// Unique Game Engine ID
		std::string m_type;				// Game Programmer Defined TYPE
		Vector m_position;				// Position in Game world

	public:
		Object();

		//Destroy Object, Remove from Game world
		virtual ~Object();

		// Set Object ID
		void setId(int new_id);

		// Get Object ID
		int getId() const;

		// Set Object type
		void setType(std::string new_type);

		// Get Object type
		std::string getType() const;

		// Set Object position in world
		void setPosition(Vector new_pos);
		
		// Get Object postion in world
		Vector getPosition() const;

		// Handle event
		// Return 0 if ignored, else 1 if handled
		virtual int eventHandler(const Event* p_e);

		// Draw Object
		virtual int draw();
	};

}

