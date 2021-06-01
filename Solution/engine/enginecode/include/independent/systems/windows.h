/** \file windows.h
*/

#pragma once // Compile once

#include "system.h" // Include system.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class WindowsSystem
	\brief A class of windows system, contains functions for systems, utilises class SystemSignal. 
	* Acts as an interface class for window systems. Inherits from class System.
	*/
	class WindowsSystem : public System
	{
	public: // Public members
		virtual void start(SystemSignal init, ...) override = 0; //!< Function, start the system (not implemented here)
		virtual void stop(SystemSignal close, ...) override = 0; //!< Function, start the system (not implemented here)
	};
}