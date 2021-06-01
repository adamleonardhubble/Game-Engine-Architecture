/** \file timer.h
*/

#pragma once // Compile once
 
#include "systems/system.h" // Include system.h file

#include "systems/log.h" // Include log.h file

#include <chrono> // Include chrono

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class chronoTimer
	\brief A class of chrono system, able to calculate time passed from one frame to another. 
	* Able to find the duration of code execution that is time pointed. Able to calculate runtime 
	* duration using time passed from frames. Inherits from System class.
	*/
	class chronoTimer : public System
	{
	private: // Private members

		static std::chrono::duration<float> timeCounter; //!< Chrono system timestep, used to calculate time passed since last the frame (seconds)
		static std::chrono::high_resolution_clock::time_point m_timeStart; //!< Time point instance, 'timeStart'
		static std::chrono::high_resolution_clock::time_point m_timeStop; //!< Time point instance, 'timeStop'

		static std::chrono::duration<float> frameCounter; //!< Chrono system timestep, used to calculate frames passed per seconds (FPS)
		static std::chrono::high_resolution_clock::time_point m_frameStart; //!< Time point instance, 'frameStart'
		static std::chrono::high_resolution_clock::time_point m_frameStop; //!< Time point instance, 'frameStop'

		static bool m_bTimerInstance; //!< Boolean variable, used to identify if there is a current instance of the chronoTimer class

		static std::shared_ptr<chronoTimer> m_pTimer; //!< Pointer to class instance

	public: // Public members
		//! Return or create the chrono timer class instance, instance getter
		/*!
		\return A pointer to the chrono timer class (the class object instance)
		*/
		static std::shared_ptr<chronoTimer> getTimerInstance();

		//! Default constructor
		chronoTimer() {};

		//! Destructor
		~chronoTimer() {};

		void start(SystemSignal init, ...); //!< Override function, start chrono timer system

		void stop(SystemSignal close, ...); //!< Override function, stop chrono timer system

		static float m_clockSecondsPassed; //!< Float variable, stores the time passed from two time points (seconds)
		
		static void startTimeCounter(); //!< Function, start time point

		//! Calculate time passed from two time points
		/*!
		\return A float representing the time passed from two time points (seconds)
		*/
		static float stopTimeCounter();

		static float m_frameSecondsPassed; //!< Float variable, stores the time passed from last frame made (seconds)

		//! Calculate time passed since last frame
		/*!
		\return A float representing the time passed since the last frame was made (seconds)
		*/
		static float frameCount();

		static float m_runtimeDuration; //!< Float variable, store time elapsed since runtime (runtime duration)
	};
}

//! Macro functions, start and stop chrono system and return calculated timestep(s) by calling relative functions and returning variable(s)
#define CHRONO_CLOCK_START		Engine::chronoTimer::startTimeCounter(); //!< \def Macro function definition, start chrono timer system at time point 'timeStart'
#define CHRONO_CLOCK_STOP		Engine::chronoTimer::stopTimeCounter(); //!< \def Macro function definition, stop chrono timer system at time point 'timeStop'
#define CHRONO_FRAMERATE		Engine::chronoTimer::frameCount(); //!< \def Macro function definition, stop chrono timer system at time point 'frameStop'
#define CHRONO_TIMEPASSED		Engine::chronoTimer::m_frameSecondsPassed; //!< \def Macro function definition, return 'frameSecondsPassed'
#define CHRONO_RUNTIME			Engine::chronoTimer::m_runtimeDuration += Engine::chronoTimer::m_frameSecondsPassed; //!< \def Macro function definition, calculate application runtime duration from continual addition of 'frameSecondsPassed'

//! Macro functions, output chrono system 'FPS', 'seconds' and 'runtime duration' relative to the set time points, using spdlog logger system
#define CHRONO_SHOW_SECONDS		Engine::MyLogger::getSpdlog()->info("Time elapsed since last frame: {0}", (float) Engine::chronoTimer::m_frameSecondsPassed); //!< \def Macro function definition, output type 'info' to logger console of type 'seconds' from the chrono system
#define CHRONO_SHOW_FPS			Engine::MyLogger::getSpdlog()->info("FPS: {0}", (int) 1.0f / Engine::chronoTimer::m_frameSecondsPassed); //!< \def Macro function definition, output type 'info' to logger console of type 'FPS' from the chrono system