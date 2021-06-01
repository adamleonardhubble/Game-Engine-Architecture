/** \file system.h
*/

#pragma once // Compile once

#include <cstdarg> // Include variadic functions

#include <memory> // Include memory management suite, use of smart pointers

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class SystemSignal
	\brief An enumerator type class, containing no enumertors
	*/
	enum class SystemSignal { None = 0 };

	/*!
	\class System
	\brief Contains functions for systems, utilises class SystemSignal. Acts as
	* an interface class for all systems.
	*/
	class System
	{
	public: // Public members
		//! Default constructor
		virtual ~System() {};
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; //!< Function, start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; //!< Function, stop the system
	};
}
