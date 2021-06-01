/** \file GLFWWindowImplementation.h
*/

#pragma once // Compile once

#include "core/core.h" // Include core.h file

#include "core/keyCodes.h" // Include keyCodes.h file

#include "platform/windows/window.h" // Include window.h file

#include "events/keyEvent.h" // Include keyEvent.h file
#include "events/mouseEvent.h" // Include mouseEvent.h file
#include "events/windowEvent.h" // Include windowEvent.h file

#include "platform/glfw/GLFWGraphicsContext.h" // Include graphicsContext.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class GLFWWindowImpl
	\brief Contains functions and variables for initialising
	* a GLFW application window. Inherits from class Window.
	*/
	class GLFWWindowImpl : public Window
	{
	private: // Private members
		float m_viewportWidth; //!< Float, set window viewport width

		float m_viewportHeight; //!< Float, set window viewport height

		GLFWwindow* m_nativeWindow; //!< Raw pointer to a GLFWwindow instance, make window

		//! Initialise window with properties
		/*!
		\param A reference to the WindowProperties class (window properties)
		*/
		void init(const WindowProperties& properties) override;

		void close() override; //!< Override function, destroy GLFW window when closed

		WindowProperties m_properties; //!< Create instance of struct 'WindowProperties' (member accessor)

		std::function<void(Event&)> m_callback; //!< onEvent callback function (bound to Application::onEvent(e))

	public: // Public members
		//! Constructor, intialise GLFW window with properties
		/*!
		\param A reference to the WindowProperties class (window properties)
		*/
		GLFWWindowImpl(const WindowProperties& properties);

		//!< Destructor
		~GLFWWindowImpl(); 

		//! Update the window
		/*!
		\param timestep A float representing the window timestep (time passed)
		*/
		void onUpdate(float timestep) override;

		//! Resize window dimensions
		/*!
		\param width A integer representing the window width dimension (resize)
		\param height A integer representing the window height dimension (resize)
		*/
		void onResize(unsigned int width, unsigned int height) override;

		//! Set vSync activeness of window
		/*!
		\param vSync A boolean representing the window vSync activeness
		*/
		void setVSync(bool vSync) override;

		//! Set fullscreen mode activeness of window
		/*!
		\param fullscreen A boolean representing the window fullscreen mode activeness
		*/
		void setFullscreenMode(bool fullscreen) override;

		//! Set the event callback
		/*!
		\param callback A event which gets passed to the event dispatcher
		*/
		void setEventCallback(const std::function<void(Event&)> & callback) override;

		//! Return the window width dimension
		/*!
		\return A integer representing the window width dimension
		*/
		inline unsigned int getWidth() const override { return m_properties.m_width; }

		//! Return the window height dimension
		/*!
		\return A integer representing the window height dimension
		*/
		inline unsigned int getHeight() const override { return m_properties.m_height; }

		//! Return the viewport width dimension
		/*!
		\return A integer representing the viewport width dimension
		*/
		inline float getViewportWidth() const override { return m_viewportWidth; }

		//! Return the viewport height dimension
		/*!
		\return A integer representing the viewport height dimension
		*/
		inline float getViewportHeight() const override { return m_viewportHeight; }

		//! Return the native window
		/*!
		\return A pointer to a window instance (GLFW window)
		*/
		inline void* getNativeWindow() const override { return m_nativeWindow; }

		//! Return fullscreen mode activeness of window
		/*!
		\return A boolean representing the window fullscreen mode activeness
		*/
		inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; }

		//! Return vSync activeness of window
		/*!
		\return A boolean representing the window vSync activeness
		*/
		inline bool isVSync() const override { return m_properties.m_isVSync; }

	};
}