#pragma once

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#define LM df::LogManager::getInstance()

#include <stdio.h>
#include <stdarg.h>


#include "Manager.h"

namespace df {

	const std::string LOGFILE_NAME = "dragonfly.log";

	class LogManager : public Manager
	{
	private:
		LogManager();									// private since singleton
		LogManager(LogManager const&);					// Don't allow copy
		void operator=(LogManager const&);
		bool m_do_flush;
		FILE* m_p_f;

	public:
		~LogManager();

		// Get one and only instance of log manager
		static LogManager& getInstance();

		// Startup LogManager
		int startUp();

		// Shutdown LogMananger
		void shutDown();

		// Set flush of logfile after each write
		void setFlush(bool do_flush = true);
		
		// Write to LogFile
		int writeLog(const char* fmt, ...) const;
	};
}

#endif

