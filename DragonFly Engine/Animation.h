#pragma once

#include<string>

#include "Sprite.h"
#include "Box.h"

namespace df {

	class Animation
	{
	private:
		Sprite* m_p_sprite;					// Sprite associated with Animation
		std::string m_name;					// Sprite name in Resource manager
		int m_index;						// Current index frame for sprite
		int m_slowdown_count;				// Slowdown counter


	public:
		// Animation Constructor
		Animation();

		// Set Associated sprite to new one.
		// Note, Sprite is managed by ResourceManager
		// Set sprite index to 0 (First Frame)
		void setSprite(Sprite* p_new_sprite);

		// Return pointer to associated sprite
		Sprite* getSprite() const;

		// Set sprite name (in Resource Manager)
		void setName(std::string new_name);

		// Get sprite name (in Resource Manager)
		std::string getName() const;

		// set index of current sprite frame to be displayed
		void setIndex(int new_index);

		// Get index of current sprite frame to be displayed
		int getIndex() const;

		// Set animation slowdown count (-1 means stop animation)
		void setSlowdownCount(int new_slowdown_count);

		// Set animation slowdown count (-1 means stop animation)
		int getSlowdownCount() const;

		// Draw single frame centered at position (x,y)
		// Drawing accounts for slowdown, and advances sprite frame
		// Return 0 if ok, else -1
		int draw(Vector position);


		// Get Bounding box of associated sprite
		Box getBox() const;
	};

}
