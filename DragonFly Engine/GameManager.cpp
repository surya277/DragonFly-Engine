#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Clock.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "EventStep.h"


#include <iostream>
#include <Windows.h>

const int FRAME_TIME_DEFAULT = 33;

namespace df {

	GameManager::GameManager() {
		setType("GameManager");
		game_over = false;
		frame_time = FRAME_TIME_DEFAULT;
	}


	//Singleton Instance
	//
	GameManager& GameManager::getInstance() {
		static GameManager GameManagerSingle;
		return GameManagerSingle;
	}


	// Startup all GameManager Services
	int GameManager::startUp() {
		if (Manager::isStarted())
			LM.writeLog("GameManager has already been started\n");

		timeBeginPeriod(1);
		LM.startUp();
		WM.startUp();
		DM.startUp();
		WM.setBoundary(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
		WM.setView(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
		LM.writeLog("Game Manager Started. \n");
		return 0;
	}


	// ShutDown all Game Manager Services
	void GameManager::shutDown() {
		timeEndPeriod(1);
		setGameOver(true);
		LM.writeLog("Game Manager Shuting down. \n");
	}

	// Run Game Loop
	void GameManager::run() {
		Clock clock;
		int frame_count = 0;
		while (!game_over) {
			long int start_time = clock.delta();

			EventStep eventStep(++frame_count);
			onEvent(&eventStep);

			IM.getInput();
			// Get Input
			
			WM.update();
			
			WM.draw();
			DM.drawString(df::Vector(7, 10), "HELLO", df::CENTER_JUSTIFIED, df::BLUE);
			//DM.drawCh(Vector(0, 0), '-',df::YELLOW);
			DM.swapBuffers();
			
			
			long int end_time = clock.split() / 1000000;
			//std::cout << frame_time << "\n";
			//std::cout << end_time;
			//LM.writeLog("sleep_time: %d \n", frame_time - (end_time/1000));
			Sleep((frame_time - end_time));
			
		}
	}



	// Set GameOver status to recieved boolean
	void GameManager::setGameOver(bool new_game_over) {
		if (new_game_over)
			game_over = new_game_over;
	}


	// Get GameOver Status
	bool GameManager::getGameOver() const {
		return game_over;
	}


	// Return frame Time
	int GameManager::getFrameTime() const {
		return frame_time;
	}

}