/*!********************************************************************
* File:	Logger.h
*
* \brief	Class that represents a log file that can be used for
*			debugging purposes. Note that this class is thread safe.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once
#include <string>
#include <cstdarg>
#include <SFML/System.hpp>

namespace DE
{
	class Logger
	{
	public:
		/*!
		*	\brief	Enum for representing the level of log message.
		*/
		enum MessageLevel
		{
			eLogComment,
			eLogMessage,
			eLogWarning,
			eLogError
		};

		/*!
		*	\brief	Returns or creates and then returns the
		*			log system singleton.
		*/
		static Logger* Instance();

		/*!
		*	\brief	Opens the log file with the specified file name.
		*	\param[in] logFile The filename of the log file.
		*	\return True if sucessfully opened the log file, false otherwise.
		*/
		bool openLogFile(const char* logFile);

		/*!
		*	\brief	Writes a message of a certain level to the log file.
		*	\param[in] level The level of the message.
		*	\param[in] The message as a char array.
		*/
		void writeToLogFile(MessageLevel level, const char* message, ...);

		/*!
		*	\brief	Closes the log file that is currently open.
		*	\return True if sucessfully closed the log file, false otherwise.
		*/
		bool closeLogFile();

		/*!
		*	\brief	Embedded class to make sure instance gets cleaned up.
		*/
		friend class Cleanup;
		class Cleanup
		{
		public:
			~Cleanup();
		};

	private:
		/*!
		*	\brief	Constructor for Logger class.
		*/
		Logger() {};

		/*!
		*	\brief	Copy Constructor for Logger class.
		*/
		Logger(Logger const&) {};

		/*!
		*	\brief	Assignment operator for Logger class.
		*/
		Logger& operator=(Logger const&) {};

		/*!
		*	\brief	Destructor for Logger class.
		*/
		virtual ~Logger();

	private:
		static Logger*		m_instance;	///< The instance of the Logger class.
		static sf::Mutex	m_mutex;	///< Mutex to make sure logger is thread safe
		FILE*				m_logFile;	///< The actual log file to write to.
	};
}