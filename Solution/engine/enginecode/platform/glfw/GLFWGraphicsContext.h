/** \file GLFWGraphicsContext.h
*/

#pragma once // Compile once

#include "platform/windows/graphicsContext.h" // Include graphicsContext.h file

#include "core/core.h" // Include core.h file

#include <glad/glad.h> // Include glad.h file

#include <GLFW/glfw3.h> // Include glfw3.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class GLFWGraphicsContext
	\brief Contains functions for initialising application windows,
	* specific to OpenGL GLFW API. Inherits class GraphicsContext. 
	*/
	class GLFWGraphicsContext : public GraphicsContext
	{
	private: // Private members
		GLFWwindow* m_Window; //!< Raw pointer to a GLFWwindow instance, make window

	public: // Public members
		//! Constructor, set GLFW window
		/*!
		\param A pointer to a GLFWwindow object instance
		*/
		GLFWGraphicsContext(GLFWwindow* window); 

		void init() override; //!< Override function, initialise GLFW graphics context

		void swapBuffers() override; //!< Override function, swap buffers of the GLFW graphics context window

	};
}
