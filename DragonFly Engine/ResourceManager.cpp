#include <fstream>

#include "ResourceManager.h"
#include "LogManager.h"

namespace df {

	ResourceManager::ResourceManager() {
		m_sprite_count = 0;
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
		int frame, width, height, slowdown;
		std::string color;
		Color spriteColor;
		if (spritefile.is_open()) {

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

		Frame* frame_string = new Frame();

		// Get each frame and set their attributes
		for (int i = 1; i < frame; i++) {
			for (int j = 1; j < height; j++) {
				getline(spritefile, line);
				frame_string->setString(line);
			}
			frame_string->setHeight(height);
			frame_string->setWidth(width);
			loaded_sprite->addFrame(*frame_string);
		}

		// Close File
		spritefile.close();

		// Set label
		loaded_sprite->setLabel(label);

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


	


}
