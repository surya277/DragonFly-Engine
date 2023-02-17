#pragma once

#include <string>

#include "Vector.h"
#include "Event.h"
#include "Animation.h"
#include "Box.h"

namespace df {

	enum Solidness {
		HARD,
		SOFT,
		SPECTRAL
	};


	class Object
	{
	private:
		int m_id;						// Unique Game Engine ID
		std::string m_type;				// Game Programmer Defined TYPE
		Vector m_position;				// Position in Game world
		int m_altitude;					// Layer to be drawn in (0 to MAX)
		Vector m_direction;				// Direction of Object
		float m_speed;					// Speed of Object
		Solidness m_solidness;			// Solidness of Object
		bool m_no_soft;					// True if won't move onto soft objects
		Animation m_animation;			// Animation associated with Object
		Box m_box;						// Box for sprite boundary and Collsions
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


		// Set altitude of Object
		// return 0 if ok, else -1
		int setAltitude(int new_altitude);

		// Return Altitude of object
		int getAltitude() const;



		// SPEED DIRECTION VELOCITY

		// Set Speed of Object
		void setSpeed(float speed);

		// Get speed of Object
		float getSpeed() const;

		// Set direction of Object
		void setDirection(Vector new_direction);

		// Get direction of Object
		Vector getDirection() const;

		// Set direction and speed of Object
		void setVelocity(Vector new_velocity);

		// Get velocity of object based on direction and speed
		Vector getVelocity() const;

		// Predict Object position based on speed and direction
		// Return predicted position
		Vector predictPosition();



		// SOLIDNESS

		// True if hard or soft, else false
		bool isSolid() const;

		// Set Object Solidness, with checks for consistency
		// Return 0 if ok, else -1
		int setSolidness(Solidness new_solid);

		// Return object solidness
		Solidness getSolidness() const;


		// SOFT COLLISION
		
		// Set 'no soft' setting (True - Cannot move onto SOFT Objects
		void setNoSoft(bool new_no_soft = true);

		// Get no soft setting
		bool getNoSoft() const;


		// ANIMATION

		
		// Set sprite for this Object to animate
		// Return 0 if ok, else -1
		int setSprite(std::string sprite_label);

		// Set Animation for this object to new one
		// Set bounding box to size of associated Sprite
		void setAnimation(Animation new_animation);

		// Get Animation for this Object
		Animation getAnimation() const;

		// Draw Object Animation
		// Return 0 if ok,else -1
		virtual int draw();


		// BOUNDING BOXES
		
		// Set Object's bounding box
		void setBox(Box new_box);

		// Get Object's bounding box
		Box getBox() const;
	};

}

