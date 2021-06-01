/** \file timer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "systems/timer.h" // Include timer.h file

namespace Engine // Engine namespace
{
	#pragma region Initialise static members in class, class specific
	float chronoTimer::m_clockSecondsPassed = 0.0f; // Initialise float 'clockSecondsPassed' to '0' (default)
	float chronoTimer::m_frameSecondsPassed = 0.0f; // Initialise float 'frameSecondsPassed' to '0' (default)

	float chronoTimer::m_runtimeDuration = 0.0f; // Intialise float 'runtimeDuration' to '0' (default)

	bool chronoTimer::m_bTimerInstance = false; // Initialise bool 'm_bTimerInstance' to false (there are no instances of the chronoTimer class made)

	std::shared_ptr<Engine::chronoTimer> chronoTimer::m_pTimer = nullptr; // Intialise pointer, set to NULL upon application (class instance pointer)

	std::chrono::duration<float> chronoTimer::timeCounter = m_timeStop - m_timeStart; // Chrono system timestep, used to calculate time passed since last the frame (seconds)
	std::chrono::high_resolution_clock::time_point chronoTimer::m_timeStart = std::chrono::high_resolution_clock::now(); // Time point instance, timeStart
	std::chrono::high_resolution_clock::time_point chronoTimer::m_timeStop = std::chrono::high_resolution_clock::now(); // Time point instance, timeStop

	std::chrono::duration<float> chronoTimer::frameCounter = m_frameStop - m_frameStart; // Chrono system timestep, used to calculate frames passed per seconds (FPS)
	std::chrono::high_resolution_clock::time_point chronoTimer::m_frameStart = std::chrono::high_resolution_clock::now(); // Time point instance, frameStart
	std::chrono::high_resolution_clock::time_point chronoTimer::m_frameStop = std::chrono::high_resolution_clock::now(); // Time point instance, frameStop

	std::shared_ptr<chronoTimer> chronoTimer::getTimerInstance() // Initialiser function, check and or create class instance (set to pointer)
	{
		if (!m_bTimerInstance) // If 'm_bTimerInstance' is false (there is no pointer, appointed to the class)
		{
			m_pTimer = std::shared_ptr<chronoTimer> (new chronoTimer()); // Set pointer to a new instance of the chronoTimer class (access class members and functions)
			m_bTimerInstance = true; // Set 'm_bTimerInstance' to true (there is a pointer appointed to class)
			return m_pTimer; // Return the pointer
		}
		else // If 'bTimerInstance' is true (there is a pointer appointed to class already)
		{
			return m_pTimer; // Return the pointer (class instance)
		}
	}
	#pragma endregion

	void chronoTimer::start(SystemSignal init, ...) // Function, start chrono timer system
	{
		m_frameStart = std::chrono::high_resolution_clock::now(); // Start chrono frame start (intial point), when function called (at runtime entry)
	}

	void chronoTimer::stop(SystemSignal close, ...) // Function, stop chrono timer system
	{
		m_pTimer = nullptr; // Set 'm_pTimer' to NULL, there is no instance of chronoTimer
		m_bTimerInstance = false; // Set 'm_bTimerInstance' to false, there is no instance of chronoTimer
	}

	void chronoTimer::startTimeCounter() // Function, start timer point when function called
	{
		m_timeStart = std::chrono::high_resolution_clock::now(); // Set chrono timer start, when function called
	}

	float chronoTimer::stopTimeCounter() // Function, stop timer point when function called and return time passed (seconds)
	{
		m_timeStop = std::chrono::high_resolution_clock::now(); // Set chrono timer end, when function called

		timeCounter = m_timeStop - m_timeStart; // Calculate duration from start time point to end time point, equating to the time passed

		m_clockSecondsPassed = timeCounter.count(); // Set 'clockSecondsPassed' to the time passed (timestep - difference from start to end time points)

		return m_clockSecondsPassed; // Return the time passed (accumulated)
	}

	float chronoTimer::frameCount() // Function, calculates time passed since the last frame was made
	{
		m_frameStop = std::chrono::high_resolution_clock::now(); // Set chrono timer end, when function called (starts intially in application constructor, at runtime entry)

		frameCounter = m_frameStop - m_frameStart; // Calculate duration from start time point to end time point, equating to the time passed

		m_frameStart = std::chrono::high_resolution_clock::now(); // Set chrono timer start, when function called

		m_frameSecondsPassed = frameCounter.count(); // Set 'frameSecondsPassed' to the time passed (timestep - difference from start to end time points)
		 
		return m_frameSecondsPassed; // Return the time passed (accumulated)
	}
}


	