/** \file GLFWGraphicsContext.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "platform/glfw/GLFWGraphicsContext.h" // Include GLFWGraphicsContext.h file

namespace Engine // Engine namespace
{
	GLFWGraphicsContext::GLFWGraphicsContext(GLFWwindow* window) : m_Window(window) // Constructor, set window
	{

	}

	void GLFWGraphicsContext::init() // Function, initialise GLFW graphics context
	{
		glfwMakeContextCurrent(m_Window); // Make window the current GLFW context
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // Load all OpenGL functions, intialise OpenGL context
		ENGINE_ASSERT(result, "An OpenGL context (GLAD) couldn't be intialised!"); // Assert if OpenGL context couldnt be initialsied
	}

	void GLFWGraphicsContext::swapBuffers() // Function, swap buffers of the GLFW graphics context window
	{
		glfwSwapBuffers(m_Window); // Swap front and back buffers of window
	}
}