/** \file log.cpp
*/

#include "engine_pch.h" // Include precompiled headers file

#include "systems/log.h" // Include log.h file

namespace Engine // Engine namespace
{
	#pragma region Initialise static members in class, class specific
	bool MyLogger::m_bRun = true; // Set bool 'm_bRun' to true at application runtime (logger is running)

	bool MyLogger::m_bLoggerInstance = false; // Initialise bool 'm_bLoggerInstance' to false (there are no instances of the MyLogger class made)

	std::shared_ptr<MyLogger> MyLogger::m_pLogger = nullptr; // Intialise pointer, set to NULL upon application (class instance pointer)

	std::shared_ptr<spdlog::logger> MyLogger::m_pSpdlog = nullptr; // Initialise pointer, set to NULL upon application start (spdlog pointer)

	std::shared_ptr<MyLogger> MyLogger::getLoggerInstance() // Initialiser function, check and or create class instance (set to pointer)
	{
		if (!m_bLoggerInstance) // If 'm_bLoggerInstance' is false (there is no pointer, appointed to the class)
		{
			m_pLogger = std::shared_ptr<MyLogger> (new MyLogger()); // Set pointer to a new instance of the MyLogger class (access class members and functions)
			m_bLoggerInstance = true; // Set 'm_bLoggerInstance' to true (there is a pointer appointed to class)
			return m_pLogger; // Return the pointer
		}
		else // If 'bLoggerInstance' is true (there is a pointer appointed to class already)
		{
			return m_pLogger; // Return the pointer (class instance)
		}
	}
	#pragma endregion

	void MyLogger::start(SystemSignal init, ...) // Function, start logger system
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // Set spdlog output pattern, as seen within console window (start colour range, time format, logger name, text to log, end colour range)
		m_pSpdlog = spdlog::stdout_color_mt("Engine"); // Create coloured logger instance, named 'Engine'
		m_pSpdlog->set_level(spdlog::level::trace); // Set level to 'trace', outputs everything to console
	}

	void MyLogger::stop(SystemSignal close, ...) // Function, stop logger system
	{
		m_pSpdlog = nullptr; // Set 'm_pSpdlog' to NULL, upon application termination (destruction)
		m_bRun = false; // Set 'm_bRun' to false when function called, application termination (logger is not running)
		m_bLoggerInstance = false; // Set 'm_bLoggerInstance' to false, there is no instance of MyLogger
	}

	bool MyLogger::bRunning() // Function, return bRun value
	{
		return m_bRun; // Return boolean variable 'bRun' value
	}

	std::shared_ptr<spdlog::logger> MyLogger::getSpdlog() // Function, return value appointed to by pSpdlog
	{
		return m_pSpdlog; // Return pSpdlog, pointer to logging system 
	}
}