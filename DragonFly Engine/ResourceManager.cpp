#include <fstream>

#include "ResourceManager.h"
#include "LogManager.h"

namespace df {

	ResourceManager::ResourceManager() {
		setType("ResourceManager");
	}

	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager ResourceManagerSingle;
		return ResourceManagerSingle;
	}

	int ResourceManager::startUp() {
		if (Manager::isStarted())
			LM.writeLog("Resource Manager has already been started\n");
		m_sprite_count = 0;
		m_sound_count = 0;
		m_music_count = 0;
		return 0;
	}

	void ResourceManager::shutDown() {
		for (int i = 0; i < m_sprite_count; i++)
			delete m_p_sprite[i];
		
		Manager::shutDown();
	}

	// Load Sprite from file
	// Assign indicated label to sprite
	// Return 0 if ok, else -1

	int ResourceManager::loadSprite(std::string filename, std::string label) {
		//
		std::ifstream spritefile(filename);
		std::string line;
		int frame=0, width=0, height=0, slowdown=0;
		std::string color;
		Color spriteColor;
		if (spritefile.is_open()) {
			if (spritefile.good()) {
				getline(spritefile, line);
				frame = atoi(line.c_str());
				getline(spritefile, line);
				width = atoi(line.c_str());
				getline(spritefile, line);
				height = atoi(line.c_str());
				getline(spritefile, line);
				slowdown = atoi(line.c_str());
				getline(spritefile, line);
				color = line;
			}
			else {
				LM.writeLog("Failed to open file\n");
				return -1;
			}
		}

		// Set Color
		if (color == "black")
			spriteColor = df::BLACK;
		else if (color == "blue")
			spriteColor = df::BLUE;
		else if (color == "yellow")
			spriteColor = df::YELLOW;
		else if (color == "green")
			spriteColor = df::GREEN;
		else if (color == "cyan")
			spriteColor = df::CYAN;
		else if (color == "red")
			spriteColor = df::RED;
		else if (color == "magenta")
			spriteColor = df::MAGENTA;
		else if (color == "white")
			spriteColor = df::WHITE;
		else
			spriteColor = df::UNDEFINED_COLOR;


		// Set sprite attributes
		Sprite* loaded_sprite = new Sprite(frame);
		loaded_sprite->setHeight(height);
		loaded_sprite->setWidth(width);
		loaded_sprite->setSlowdown(slowdown);
		loaded_sprite->setColor(spriteColor);

		Frame frame_string;

		// Get each frame and set their attributes
		for (int i = 1; i <= frame; i++) {
			frame_string.setString("");
			for (int j = 1; j <= height; j++) {
				getline(spritefile, line);
				frame_string.setString(frame_string.getString() + line);
			}
			frame_string.setHeight(height);
			frame_string.setWidth(width);
			loaded_sprite->addFrame(frame_string);
		}

		// Close File
		spritefile.close();

		// Set label
		loaded_sprite->setLabel(label);
		m_p_sprite[m_sprite_count] = loaded_sprite;
		m_sprite_count++;

		return 0;
	}


	// Unload Sprite with indicated label
	// Return 0 if ok, else -1
	int ResourceManager::unloadSprite(std::string label) {
		
		for (int i = 0; i < m_sprite_count - 1; i++) {
			if (label == m_p_sprite[i]->getLabel()) {
				delete m_p_sprite[i];

				// Scoot over remaining
				for (int j = i; j < m_sprite_count - 1; j++) {
					m_p_sprite[j] = m_p_sprite[j + 1];
				}
				m_sprite_count--;
				return 0;
			}
		}
		return -1;
	}


	//Find Sprite with indicated label
	// Return pointer to it if found, else NULL
	Sprite* ResourceManager::getSprite(std::string label) const {

		for (int i = 0; i < m_sprite_count; i++) {
			if (label == m_p_sprite[i]->getLabel())
				return m_p_sprite[i];
		}
		return NULL;
	}


	// SOUND AND MUSIC

	// Load sound from file
	// Return 0 if ok, else -1
	int ResourceManager::loadSound(std::string filename, std::string label) {
		
		// Check if array is full
		if (m_sound_count >= MAX_SOUNDS){
			LM.writeLog("Sound Array is full.\n");
			return -1;
		}

		// Check for file
		if (sound[m_sound_count].loadSound(filename) == -1) {
			LM.writeLog("Unable to load Sound from file.\n");
			return -1;
		}

		sound[m_sound_count].setLabel(label);
		m_sound_count++;
	}

	// Remove Sound with indicated label
	// Return 0 if ok, else -1
	int ResourceManager::unloadSound(std::string label) {

		for (int i = 0; i < m_sound_count; i++) {
			if (label == sound[i].getLabel()) {
				for (int j = i; j < m_sound_count - 1; j++) {
					sound[j] = sound[j + 1];
				}
				m_sound_count--;
				return 1;
			}
		}
		LM.writeLog("Sound File not found.\n");
		return -1;
	}
	

	// Find sound with indicated label
	// Return pointer to it if found, else NULL
	Sound* ResourceManager::getSound(std::string label) {

		for (int i = 0; i < m_sound_count; i++) {
			if (label == sound[i].getLabel())
				return &sound[i];
		}

		return NULL;				// Sound not found
	}


	// Associate file with Music
	// Return 0 if ok, else -1
	int ResourceManager::loadMusic(std::string filename, std::string label) {
		
		// Check if array is full
		if (m_music_count >= MAX_MUSICS) {
			LM.writeLog("Music Array is full.\n");
			return -1;
		}

		// Check for file
		if (music[m_music_count].loadMusic(filename) == -1) {
			LM.writeLog("Unable to load Sound from file.\n");
			return -1;
		}

		music[m_music_count].setLabel(label);
		m_music_count++;
	}

	// Remove label for music with indicated label
	// Return 0 if ok, else -1
	int ResourceManager::unloadMusic(std::string label) {

		for (int i = 0; i < m_music_count; i++) {
			if (label == music[i].getLabel()) {
				music[i].setLabel("");						// Music cannot be copied so we set the label to "" so it can't be accessed
				m_music_count--;
				return 1;
			}
		}
		LM.writeLog("Music File not found.\n");
		return -1;
	}

	// Find Music with indiacted label
	// Return pointer to it if found, else NULL
	Music* ResourceManager::getMusic(std::string label) {

		for (int i = 0; i < m_music_count; i++) {
			if (label == music[i].getLabel())
				return &music[i];
		}

		return NULL;
	}
}
