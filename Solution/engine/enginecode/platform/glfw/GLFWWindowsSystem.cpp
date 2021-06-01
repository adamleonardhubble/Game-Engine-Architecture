/** \file GLFWWindowsSystem.cpp
*/

#include "engine_pch.h" // Include precompiled headers file

#include "core/core.h" // Included core.h file

#include "platform/glfw/GLFWWindowsSystem.h" // Included GLFWWindowsSystem.h file

#include <GLFW/glfw3.h> // Include glfw3.h file

namespace Engine // Engine namespace
{
	bool GLFWWindowsSystem::m_bWindowsSystemInstance = false; // Set bool 'm_bWindowsSystemInstance' to false (there are no instances of the GLFWWindowsSystem class made)

	std::shared_ptr<GLFWWindowsSystem> GLFWWindowsSystem::m_pWindowSystem = nullptr; // Intialise pointer, set to NULL upon application (class instance pointer)

	std::shared_ptr<GLFWWindowsSystem> GLFWWindowsSystem::getInstance() // Initialiser function, check and or create class instance (set to pointer)
	{
		if (!m_bWindowsSystemInstance) // If 'm_bWindowsSystemInstance' is false (there is no pointer, appointed to the class)
		{
			m_pWindowSystem = std::shared_ptr<GLFWWindowsSystem>(new GLFWWindowsSystem()); // Set pointer to a new instance of the GLFWWindowsSystem class (access class members and functions)
			m_bWindowsSystemInstance = true; // Set 'm_bWindowsSystemInstance' to true (there is a pointer appointed to class)
			return m_pWindowSystem; // Return the pointer
		}
		else // If 'm_bWindowsSystemInstance' is true (there is a pointer appointed to class already)
		{
			return m_pWindowSystem; // Return the pointer (class instance)
		}
	}

	void GLFWWindowsSystem::start(SystemSignal init, ...) // Function, start GLFW windows system
	{
		int success = glfwInit(); // Intialise GLFW library, set result of intialisation
		ENGINE_ASSERT(success, "GLFW library could not be initialised!"); // Assert if GLFW library not intialised (call breakpoint)

		m_bGLFWInitialized = true; // Set 'm_bGLFWInitialized' to true (GLFW library has been intialised)
	}

	void GLFWWindowsSystem::stop(SystemSignal close, ...) // Function, stop GLFW windows system
	{
		glfwTerminate(); // Terminate the GLFW library

		m_pWindowSystem = nullptr; // Set 'm_pWindowSystem' to NULL, upon application termination (destruction)
		m_bGLFWInitialized = false; // Set 'm_bGLFWInitialized' to false (GLFW library has been unitialised)
		m_bWindowsSystemInstance = false;  // Set 'm_bWindowsSystemInstance' to false, there is no instance of GLFWWindowsSystem
	}
}