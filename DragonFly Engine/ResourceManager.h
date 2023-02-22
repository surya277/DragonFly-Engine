#pragma once

#include <string>

#include "Manager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

#define RM df::ResourceManager::getInstance()

namespace df {

	const int MAX_SPRITES = 1000;
	const int MAX_SOUNDS = 64;
	const int MAX_MUSICS = 64;

	class ResourceManager : public Manager
	{
	private:
		ResourceManager();									// Private
		ResourceManager(ResourceManager const&);			// Don't allow copy
		void operator=(ResourceManager const&);				// Don't allow assignment
		Sprite* m_p_sprite[MAX_SPRITES];					// Array of sprites
		int m_sprite_count;

		Sound sound[MAX_SOUNDS];							// Array of soumd buffers
		int m_sound_count;									// Count of number of loaded sounds
		Music music[MAX_MUSICS];							// Array of music buffers
		int m_music_count;									// Count of number of loaded musics

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


		// SOUND AND MUSIC

		// Load sound from file
		// Return 0 if ok, else -1
		int loadSound(std::string filename, std::string label);

		// Remove Sound with indicated label
		// Return 0 if ok, else -1
		int unloadSound(std::string label);

		// Find sound with indicated label
		// Return pointer to it if found, else NULL
		Sound* getSound(std::string label);

		// Associate file with Music
		// Return 0 if ok, else -1
		int loadMusic(std::string filename, std::string label);

		// Remove label for music with indicated label
		// Return 0 if ok, else -1
		int unloadMusic(std::string label);

		// Find Music with indiacted label
		// Return pointer to it if found, else NULL
		Music* getMusic(std::string label);
	};

}

