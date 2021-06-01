/** \file windowEvent.h
*/

#pragma once // Compile once

#include "events/event.h" // Include event.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class WindowCloseEvent
	\brief Contains variables and functions for the window close event, inherits from class Event
	*/
	class WindowCloseEvent : public Event
	{
	public: // Public members
		//! Default constructor 
		WindowCloseEvent() {};

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::WindowClose; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::WindowClose; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/*!
	\class WindowResizeEvent
	\brief Contains variables and functions for the window resize event, inherits from class Event
	*/
	class WindowResizeEvent : public Event
	{
	private: // Private members
		int m_Width; //!< Integer variable, width of window
		
		int m_Height; //!< Integer variable, width of window

	public: // Public members
		//! Constructor, set width and height of window
		/*!
		\param windowWidth A integer representing the window width
		\param windowHeight A integer representing the window height
		*/
		WindowResizeEvent(int windowWidth, int windowHeight) : m_Width(windowWidth), m_Height(windowHeight) {};

		//! Return the window width dimension
		/*!
		\return A integer representing the window width dimension
		*/
		inline int getWidth() const { return m_Width; }

		//! Return the window height dimension
		/*!
		\return A integer representing the window height dimension
		*/
		inline int getHeight() const { return m_Height; }

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::WindowResize; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::WindowResize; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryWindow; }

	};

	/*!
	\class WindowMovedEvent
	\brief Contains variables and functions for the window moved event, inherits from class Event
	*/
	class WindowMovedEvent : public Event
	{
	private: // Private members
		float m_windowPositionX; //!< Float variable, window position 'X' axis

		float m_windowPositionY; //!< Float variable, window position 'Y' axis

	public: // Public members
		//! Constructor, set window positions 'X' and 'Y' axis
		/*!
		\param positionX A float representing the window position in the 'X' axis
		\param positionY A float representing the window position in the 'Y' axis
		*/
		WindowMovedEvent(float positionX, float positionY) : m_windowPositionX(positionX), m_windowPositionY(positionY) {};

		//! Return the window position in the 'X' axis
		/*!
		\return A float representing the window position in the 'X' axis
		*/
		inline float getWindowPositionX() const { return m_windowPositionX; }

		//! Return the window position in the 'Y' axis
		/*!
		\return A float representing the window position in the 'Y' axis
		*/
		inline float getWindowPositionY() const { return m_windowPositionY; }

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::WindowMoved; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::WindowMoved; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/*!
	\class FocusEvent
	\brief Contains variables and functions for the focus event, inherits from class Event
	*/
	class FocusEvent : public Event
	{
	protected: // Protected members
		//! Constructor, set focus positon for 'X' and 'Y' axis
		/*!
		\param focusPositionX A float representing the focus position in the 'X' axis
		\param focusPositionY A float representing the focus position in the 'Y' axis
		*/
		FocusEvent(float focusPositionX, float focusPositionY) : m_focusPositionX(focusPositionX), m_focusPositionY(focusPositionY) {};

		float m_focusPositionX; //!< Float variable, focus position 'X' axis

		float m_focusPositionY; //!< Float variable, focus position 'Y' axis

	public: // Public members
		//! Return the focus position in the 'X' axis
		/*!
		\return A float representing the focus position in the 'X' axis
		*/
		inline float getFocusPositionX() const { return m_focusPositionX; } 

		//! Return the focus position in the 'Y' axis
		/*!
		\return A float representing the focus position in the 'Y' axis
		*/
		inline float getFocusPositionY() const { return m_focusPositionY; } 

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryWindow; } 

	};

	/*!
	\class WindowFocusEvent
	\brief Contains variables and functions for the window focus event, inherits from class FocusEvent
	*/
	class WindowFocusEvent : public FocusEvent
	{
	public: // Public members
		//! Constructor, set focus positon for 'X' and 'Y' axis
		/*!
		\param focusPositionX A float representing the focus position in the 'X' axis
		\param focusPositionY A float representing the focus position in the 'Y' axis
		*/
		WindowFocusEvent(float focusPositionX, float focusPositionY) : FocusEvent(focusPositionX, focusPositionY) {};

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::WindowFocus; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::WindowFocus; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/*!
	\class WindowLostFocusEvent
	\brief Contains variables and functions for the window lost focus event, inherits from class FocusEvent
	*/
	class WindowLostFocusEvent : public FocusEvent
	{
	public: // Public members
		//! Constructor, set lost focus positon for 'X' and 'Y' axis
		/*!
		\param focusPositionX A float representing the lost focus position in the 'X' axis
		\param focusPositionY A float representing the lost focus position in the 'Y' axis
		*/
		WindowLostFocusEvent(float focusPositionX, float focusPositionY) : FocusEvent(focusPositionX, focusPositionY) {};

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::WindowLostFocus; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::WindowLostFocus; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};
}