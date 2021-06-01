/** \file GLFWWindowsSystem.h
*/

#pragma once // Compile once

#include "systems/windows.h" // Include windows.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class GLFWWindowsSystem
	\brief A class of GLFW windows system, able to intialise GLFW library 
	* specific to GLFW API window use. Inherits from class WindowsSystem.
	*/
	class GLFWWindowsSystem : public WindowsSystem
	{
	private: // Private members
		static bool m_bWindowsSystemInstance; //!< Boolean variable, used to identify if there is a current instance of the GLFWWindowsSystem class

		bool m_bGLFWInitialized; //!< Boolean variable, used to identify if GLFW library has been intialised
		
		static std::shared_ptr<GLFWWindowsSystem> m_pWindowSystem; //!< Pointer to GLFWwindowsSystem class instance

	public: // Public members
		//! Return or create the GLFW windows system class instance, instance getter
		/*!
		\return A pointer to the GLFW windows system class (the class object instance)
		*/
		static std::shared_ptr<GLFWWindowsSystem> getInstance();

		void start(SystemSignal init, ...) override; //!< Override function, start GLFW windows system
		void stop(SystemSignal close, ...) override; //!< Override function, stop GLFW windows system
	};
}