#include "LogManager.h"
#include "Utility.h"

#include <iostream>
#include <fstream>

namespace df {

	LogManager::LogManager() {
		setType("LogManager");
		m_p_f = NULL;
		m_do_flush = false;

	}


	// Starts up the Log Manager
	// Opens the Log file
	int LogManager::startUp() {
		Manager::startUp();

		errno_t file_err;
		file_err = fopen_s(&m_p_f, LOGFILE_NAME.c_str(), "w+");
		if (file_err == 0)
		{
			fputs("Log File Opened. \n", m_p_f);
		}
		else
		{
			std::cout << "File Failed to open";
		}
		return 0;
	}

	//Singleton Instance
	//
	LogManager& LogManager::getInstance() {
		static LogManager LogManagerSingle;
		return LogManagerSingle;
	}


	// Shuts down the Log Manager
	//
	void  LogManager::shutDown() {
		df::Manager::shutDown();

		if (m_p_f)
			fclose(m_p_f);
	}


	// Set Flush to true so OS writes to file immediately
	//
	void LogManager::setFlush(bool do_flush) {
		m_do_flush = do_flush;
	}


	// Write to Log File using fprintf
	//
	int LogManager::writeLog(const char* fmt, ...) const {
		//Write to Log File. Get variable number of arguments and add them to the log
		fprintf(m_p_f, "Message: %s ", df::Utility::getTimeString());
		//fprintf(m_p_f, df::Utility::getTimeString());

		va_list args;
		va_start(args, fmt);

		vfprintf(m_p_f, fmt, args);
		va_end(args);

		if (m_do_flush)
			fflush(m_p_f);

		return 1;

	}

	// Close the LogManager
	//
	LogManager::~LogManager() {
		shutDown();
	}

}