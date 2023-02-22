#include "Music.h"
#include "LogManager.h"
namespace df {

	Music::Music() {

	}

	//Associate Music buffer with file
	// Return 0 if ok, else -1
	int Music::loadMusic(std::string filename) {
		if (m_music.openFromFile(filename) == false) {
			LM.writeLog("Error loading Music from file\n");
			return -1;
		}
	}

	// Set label associated with music
	void Music::setLabel(std::string new_label) {
		m_label = new_label;
	}

	// Get label associated with music
	std::string Music::getLabel() const {
		return m_label;
	}

	// Play music
	// If loop is true, repeat play when done
	void Music::play(bool loop) {
		m_music.setLoop(loop);
		m_music.play();
	}

	// Stop sound
	void Music::stop() {
		m_music.stop();
	}

	// Pause sound
	void Music::pause() {
		m_music.pause();
	}

	// Return SFML sound
	sf::Music* Music::getMusic() {
		return &m_music;
	}
}