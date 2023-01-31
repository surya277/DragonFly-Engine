#include "LogManager.h"
#include "Utility.h"

#include <iostream>
#include <fstream>

df::LogManager::LogManager() {
	setType("LogManager");
	m_p_f = NULL;
	m_do_flush = false;

	df:LogManager::startUp();
}


// Starts up the Log Manager
// Opens the Log file
int df::LogManager::startUp() {
	df::Manager::startUp();

	errno_t file_err;
	file_err = fopen_s(&m_p_f,LOGFILE_NAME.c_str(), "w+");
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
df::LogManager& df::LogManager::getInstance() {
	static LogManager LogManagerSingle;
	return LogManagerSingle;
}


// Shuts down the Log Manager
//
void  df::LogManager::shutDown() {
	df::Manager::shutDown();

	if (m_p_f)
		fclose(m_p_f);
}


// Set Flush to true so OS writes to file immediately
//
void setFlush(bool do_flush = true) {
	if (do_flush)
		fflush(stdout);
}


// Write to Log File using fprintf
//
int df::LogManager::writeLog(const char* fmt, ...) const {
	//Write to Log File. Get variable number of arguments and add them to the log
	fprintf(m_p_f, "Message: ");
	//fprintf(m_p_f, df::Utility::getTimeString());

	va_list args;
	va_start(args, fmt);

	vfprintf(m_p_f, fmt, args);
	va_end(args);


	return 1;

}

// Close the LogManager
//
df::LogManager::~LogManager() {
	shutDown();
}