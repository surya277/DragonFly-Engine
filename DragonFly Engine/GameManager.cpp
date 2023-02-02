#include "GameManager.h"
#include "LogManager.h"
#include "Clock.h"
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
		timeBeginPeriod(1);
		LM.startUp();
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
		//while (!game_over) {
			Clock clock;
			long int start_time = clock.delta();
			LM.writeLog("Hello Log Manager \n");
			LM.writeLog("Log Manager Running. \n");
			LM.writeLog("DisplayManger::startUp() : max X is %d, max Y is %d \n", 10, 20);
			long int end_time = clock.split();
			LM.writeLog("sleep_time: %d \n", frame_time - (end_time/1000));
			Sleep(frame_time - end_time/1000);

		//}
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