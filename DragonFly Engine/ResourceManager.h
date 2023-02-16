#pragma once

#include <string>

#include "Manager.h"
#include "Sprite.h"

#define RM df::ResourceManager::getInstance()

namespace df {

	const int MAX_SPRITES = 1000;

	class ResourceManager : public Manager
	{
	private:
		ResourceManager();									// Private
		ResourceManager(ResourceManager const&);			// Don't allow copy
		void operator=(ResourceManager const&);				// Don't allow assignment
		Sprite* m_p_sprite[MAX_SPRITES];					// Array of sprites
		int m_sprite_count;

	public:
		// Get the one and only instance of the Resource Manager
		static ResourceManager& getInstance();

		// Get Resource Manager ready to manage for resources
		int startUp();

		// Shut down ResourceManager, freeing up an allocated Sprites
		void shutDown();

		// Load Sprite from file
		// Assign indicated label to sprite
		// Return 0 if ok, else -1
		int loadSprite(std::string filename, std::string label);

		// Unload Sprite with indicated label
		// Return 0 if ok, else -1
		int unloadSprite(std::string label);

		// Find Sprite with indicated lable
		// Return pointer to it if found, else NULL
		Sprite* getSprite(std::string label) const;

	};

}

