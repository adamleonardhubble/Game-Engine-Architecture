/** \file window.h
*/

#pragma once // Compile once

#include "platform/windows/graphicsContext.h" // Include graphicsContext.h file

#include "events/event.h" // Include event.h file
#include "events/windowEvent.h" // Include windowEvent.h file
#include "events/keyEvent.h" // Include keyEvent.h file
#include "events/mouseEvent.h" // Include mouseEvent.h file

#include <string> // Include string library
#include <functional> // Include functional library

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\struct WindowProperties
	\brief Contains variables for setting window properties
	*/
	struct WindowProperties
	{
		std::string m_title; //!< String, set application window title

		unsigned int m_width; //!< Unsigned integer, set window width dimension (default)

		unsigned int m_height; //!< Unsigned integer, set window height dimension (default)

		bool m_isFullScreen; //!< Boolean, set window full screen (not by default)

		bool m_isVSync; //!< Boolean, set window vSync active

		float m_aspectRatio; //!< Float, set window aspect ratio

		unsigned int m_windowedWidth; //!< Unsigned integer, set window width dimension (fullscreen to windowed mode use)

		unsigned int m_windowedHeight; //!< Unsigned integer, set window width dimension (fullscreen to windowed mode use)

		unsigned int m_windowedPositionX; //!< Unsigned integer, set window position 'X' axis (fullscreen to windowed mode use)

		unsigned int m_windowedPositionY; //!< Unsigned integer, set window position 'Y' axis (fullscreen to windowed mode use)

		//! Constructor, set window properties (passed by value)
		/*!
		\param title A string representing the window title
		\param width A integer representing the intial window width dimension
		\param height A integer representing the intial window height dimension
		\param fullscreen A boolean representing the window fullscreen mode activeness
		*/
		WindowProperties(const std::string& title = "Engine Window", unsigned int width = 800, unsigned int height = 600, 
			bool fullscreen = false) : m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen), m_aspectRatio((float)width / (float)height), 
			m_windowedHeight(height), m_windowedWidth(width), m_windowedPositionX(200), m_windowedPositionY(200) {}
	};

	/*!
	\class Window
	\brief Contains functions for initialising application windows,
	* acts as an interface for creating a GLFW window (currently)
	*/
	class Window
	{
	public: // Public members

		//! Initialise window with properties
		/*!
		\param A reference to the WindowProperties class (window properties)
		*/
		virtual void init(const WindowProperties& properties) = 0;

		virtual void close() = 0; //!< Function, destroy window when closed

		//! Default destructor
		virtual ~Window() {};

		//! Update the window
		/*!
		\param timestep A float representing the window timestep (time passed)
		*/
		virtual void onUpdate(float timestep) = 0;

		//! Resize window dimensions
		/*!
		\param width A integer representing the window width dimension (resize)
		\param height A integer representing the window height dimension (resize)
		*/
		virtual void onResize(unsigned int width, unsigned int height) = 0;

		//! Set vSync activeness of window
		/*!
		\param vSync A boolean representing the window vSync activeness
		*/
		virtual void setVSync(bool vSync) = 0;

		//! Set fullscreen mode activeness of window
		/*!
		\param fullscreen A boolean representing the window fullscreen mode activeness
		*/
		virtual void setFullscreenMode(bool fullscreen) = 0;

		//! Set the event callback
		/*!
		\param callback A event which gets passed to the event dispatcher
		*/
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0;

		//! Return the window width dimension
		/*!
		\return A integer representing the window width dimension
		*/
		virtual unsigned int getWidth() const = 0;

		//! Return the window height dimension
		/*!
		\return A integer representing the window height dimension
		*/
		virtual unsigned int getHeight() const = 0;

		//! Return the viewport width dimension
		/*!
		\return A integer representing the viewport width dimension
		*/
		virtual float getViewportWidth() const = 0;

		//! Return the viewport height dimension
		/*!
		\return A integer representing the viewport height dimension
		*/
		virtual float getViewportHeight() const = 0;

		//! Return the native window
		/*!
		\return A pointer to a window instance
		*/
		virtual void* getNativeWindow() const = 0;

		//! Return fullscreen mode activeness of window
		/*!
		\return A boolean representing the window fullscreen mode activeness
		*/
		virtual bool isFullScreenMode() const = 0;

		//! Return vSync activeness of window
		/*!
		\return A boolean representing the window vSync activeness
		*/
		virtual bool isVSync() const = 0;

		//! Create a window instance (with properties)
		/*!
		\param properties A reference to the WindowProperties class (window properties)
		*/
		static Window* create(const WindowProperties& properties = WindowProperties());
	protected: // Protected members
		std::shared_ptr<GraphicsContext> m_context; //!< Shared pointer, appointed to an instance of 'GraphicsContext' class

	};
}

