/** \file GLFWWindowInputPoller.cpp
*/

#include "engine_pch.h" // Include engine_pch.h file

#include "events/inputPoller.h" // Include inputPoller.h file

#include <GLFW/glfw3.h> // Include glw3.h file

#include "platform/glfw/GLFWWindowInputPoller.h" // Include GLFWWindowInputPoller.h file

namespace Engine // Engine namespace
{
	InputPoller* InputPoller::s_instance = new GLFWInputPoller(); // Raw pointer, create a 'InputPoller' class instance, set to a 'GLFWInputPoller' class instance

	bool GLFWInputPoller::isKeyPressedImpl(int keycode) // Function, get the key pressed status and key code if pressed (Windows API specific implementation)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow()); // Set the window pointer to the active GLFW window
		int result = glfwGetKey(window, keycode); // Set result, to the key code of the key typed during the window open
		return result == ENGINE_KEY_PRESS || result == ENGINE_KEY_REPEAT; // Return result as a key press or key repeat (true or false)
	}

	bool GLFWInputPoller::isMouseButtonPressedImpl(int button) // Function, get the mouse button pressed status (Windows API specific implementation)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow()); // Set the window pointer to the active GLFW window
		int result = glfwGetMouseButton(window, button); // Set result, to the mouse button pressed during the window open
		return result == ENGINE_KEY_PRESS; // Return result as a key press
	}

	glm::vec2 GLFWInputPoller::getMousePositionImpl() // Function, get the mouse position (Windows API specific implementation)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow()); // Set the window pointer to the active GLFW window
		
		double xPosition; // Double variable, mouse position 'X' axis
		double yPosition; // Double variable, mouse position 'Y' axis

		glfwGetCursorPos(window, &xPosition, &yPosition); // Return the mouse position relative to the window, set the position local variables to the current mouse position per axis

		return { (float)xPosition, (float)yPosition }; // Return the current mouse position (type casted)
	}

	float GLFWInputPoller::getMouseXImpl() // Function, get the mouse position in 'X' axis (Windows API specific implementation)
	{
		glm::vec2 Position = getMousePositionImpl(); // Get current mouse position

		return Position.x; // Return mouse position 'X' axis
	}

	float GLFWInputPoller::getMouseYImpl() // Function, get the mouse position in 'Y' axis (Windows API specific implementation)
	{
		glm::vec2 Position = getMousePositionImpl(); // Get current mouse position

		return Position.y; // Return mouse position 'Y' axis
	}
}