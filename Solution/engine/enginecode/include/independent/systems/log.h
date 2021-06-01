/** \file log.h
*/

#pragma once // Compile once

#include "spdlog/spdlog.h" // Include spdlog logger

#include "spdlog/sinks/stdout_color_sinks.h" // Include spdlog logger colour sinks

#include "systems/system.h" // Include system.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class MyLogger
	\brief A class of spdlog system, able to output a sequence of arguements in the forms of messages 
	* and or values from variables and functions. Able to output arguements in different visual 
	* formats, which is relative to the set use of the logger. Inherits from class System.
	*/
	class MyLogger : public System
	{
	private: // Private members

		static bool m_bRun; //!< Static boolean variable, logger system run status

		static bool m_bLoggerInstance; //!< Boolean variable, used to identify if there is a current instance of the MyLogger class

		static std::shared_ptr<MyLogger> m_pLogger; //!< Pointer to class instance

	public: // Public members
		//! Return or create the logger class instance, instance getter
		/*!
		\return A pointer to the logger class (the class object instance)
		*/
		static std::shared_ptr<MyLogger> getLoggerInstance();

		static std::shared_ptr<spdlog::logger> m_pSpdlog; //!< Create shared pointer, of type spdlog::logger (object)

		//! Return the logger system
		/*!
		\return A pointer to the logger system
		*/
		static std::shared_ptr<spdlog::logger> getSpdlog();

		//! Default constructor
		MyLogger() {};

		//! Destructor
		~MyLogger() {};

		void start(SystemSignal init, ...); //!< Override function, start logger system

		void stop(SystemSignal close, ...); //!< Override function, stop logger system

		//! Logger system run status
		/*!
		\return A boolean identifying the logger system status
		*/
		static bool bRunning();
	};
}

//! Macro functions (variadic), output messages of all spdlog logger types 
#define ENGINE_ERROR(...)		Engine::MyLogger::getSpdlog()->error(__VA_ARGS__) //!< \def Macro function definition (variadic), output type 'error' to logger console
#define ENGINE_CRITICAL(...)	Engine::MyLogger::getSpdlog()->critical(__VA_ARGS__) //!< \def Macro function definition (variadic), output type 'critical' to logger console
#define ENGINE_INFO(...)		Engine::MyLogger::getSpdlog()->info(__VA_ARGS__) //!< \def Macro function definition (variadic), output type 'info' to logger console
#define ENGINE_WARN(...)		Engine::MyLogger::getSpdlog()->warn(__VA_ARGS__) //!< \def Macro function definition (variadic), output type 'warn' to logger console
#define ENGINE_TRACE(...)		Engine::MyLogger::getSpdlog()->trace(__VA_ARGS__) //!< \def Macro function definition (variadic), output type 'trace' to logger console