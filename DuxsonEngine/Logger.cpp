#include <iostream>
#include "./Include/Logger.h"

using namespace DE;

Logger* Logger::m_instance = NULL;
sf::Mutex Logger::m_mutex;

Logger* Logger::Instance()
{
	static Cleanup cleanup;

	sf::Lock lock(m_mutex);

	//Create instance if not yet created.
	if (!m_instance)
	{
		m_instance = new Logger;
		m_instance->openLogFile("./DuxsonEngineLog.txt");
	}

	return m_instance;
}

Logger::Cleanup::~Cleanup()
{
	sf::Lock lock(m_mutex);
	delete Logger::m_instance;
	Logger::m_instance = NULL;
}

Logger::~Logger()
{
	if (m_logFile != NULL)
	{
		fclose(m_logFile);
		m_logFile = NULL;
	}
}

bool Logger::openLogFile(const char* logFile)
{
	sf::Lock lock(m_mutex);

	if (m_logFile == NULL)
	{
		fopen_s(&m_logFile, logFile, "w");
		if (m_logFile != NULL)
		{
			fprintf(m_logFile, "\n------------------------------------LOG-----------------------------------\n");
			return true;
		}
		else
		{
			std::cerr << "Problem Opening the log file. Check your read and write permissions.\n";
			return false;
		}
	}
	else
	{
		std::cerr << "There is a log file already open. Please close this before opening another.\n";
		return false;
	}
}

void Logger::writeToLogFile(MessageLevel level, const char* message, ...)
{
	sf::Lock lock(m_mutex);

	if (m_logFile == NULL)
	{
		std::cerr << "There is a no log file open - use openLogFile()\n";
		return;
	}

	if (eLogError == level)
		fprintf(m_logFile, "ERROR:   ");
	else if (eLogWarning == level)
		fprintf(m_logFile, "WARNING: ");
	else if (eLogMessage)
		fprintf(m_logFile, "MESSAGE: ");
	else
		fprintf(m_logFile, "COMMENT: ");

	va_list args;
	va_start(args, message);
	vfprintf(m_logFile, message, args);
	va_end(args);

	fprintf(m_logFile, "\n");
}

bool Logger::closeLogFile()
{
	sf::Lock lock(m_mutex);

	if (m_logFile != NULL)
	{
		fclose(m_logFile);
		m_logFile = NULL;
	}

	return true;
}
