#pragma once

#include "Manager.h"

#define GM df::GameManager::getInstance()

namespace df {

	class GameManager : public Manager
	{
	private:
		GameManager();								// private since a singleton
		GameManager(GameManager const&);			// Don't allow a copy
		void operator= (GameManager const&);		// Don't allow assignment
		bool game_over;
		int frame_time;

	public:
		// Get Singelton instance of Game Manager
		static GameManager& getInstance();

		// StartUp all GameManager Services
		int startUp();

		// ShutDown all GameManager Services
		void shutDown();

		// Run Game Loop
		void run();

		// Set GameOver Status
		// if true will stop game loop
		void setGameOver(bool new_game_over = true);

		// Get GameOver Status
		bool getGameOver() const;

		// Return frame Time
		// Frame Time -> Target time for game loop, in  milliseconds.
		int getFrameTime() const;
	};
}

