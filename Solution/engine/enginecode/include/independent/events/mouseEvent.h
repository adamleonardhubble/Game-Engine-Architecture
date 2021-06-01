/** \file mouseEvent.h
*/

#pragma once // Compile once

#include "events/event.h" // Include event.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class MouseMovedEvent
	\brief Contains variables and functions for the mouse moved event, inherits from class Event
	*/
	class MouseMovedEvent : public Event
	{
	private: // Private members
		float m_mousePositionX; //!< Float variable, mouse position 'X' axis

		float m_mousePositionY; //!< Float variable, mouse position 'Y' axis
	
	public: // Public members
		//! Constructor, set mouse position 'X' and 'Y' axis
		/*!
		\param positionY A float representing the mouse position in the 'X' axis
		\param positionY A float representing the mouse position in the 'Y' axis
		*/
		MouseMovedEvent(float positionX, float positionY) : m_mousePositionX(positionX), m_mousePositionY(positionY) {};

		//! Return the mouse position in the 'X' axis
		/*!
		\return A float representing the mouse position in the 'X' axis
		*/
		inline float getMousePositionX() const { return m_mousePositionX; }

		//! Return the mouse position in the 'Y' axis
		/*!
		\return A float representing the mouse position in the 'Y' axis
		*/
		inline float getMousePositionY() const { return m_mousePositionY; }

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::MouseMoved; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::MouseMoved; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

	};

	/*!
	\class MouseScrolledEvent
	\brief Contains variables and functions for the mouse scrolled event, inherits from class Event
	*/
	class MouseScrolledEvent : public Event
	{
	private: // Private members
		float m_scrollOffsetX; //!< Float variable, scroller offset 'X' axis

		float m_scrollOffsetY; //!< Float variable, scroller offset 'Y' axis

	public: // Public members
		//! Constructor, set scroller offset positions 'X' and 'Y' axis
		/*!
		\param positionY A float representing the scroller offset position in the 'X' axis
		\param positionY A float representing the scroller offset position in the 'Y' axis
		*/
		MouseScrolledEvent(float scrollOffsetX, float scrollOffsetY) : m_scrollOffsetX(scrollOffsetX), m_scrollOffsetY(scrollOffsetY) {};

		//! Return the scroller offset position in the 'X' axis
		/*!
		\return A float representing the scroller offset position in the 'X' axis
		*/
		inline float getXOffset() const { return m_scrollOffsetX; }

		//! Return the scroller offset position in the 'Y' axis
		/*!
		\return A float representing the scroller offset position in the 'Y' axis
		*/
		inline float getYOffset() const { return m_scrollOffsetY; }

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::MouseScrolled; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::MouseScrolled; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

	};
	
	/*!
	\class MouseButtonEvent
	\brief Contains variables and functions for the mouse button event, inherits from class Event
	*/
	class MouseButtonEvent : public Event
	{
	protected: // Protected members
		//! Constructor, set mouse button
		/*!
		\param mouseButton A integer representing the mouse button code (if pressed)
		*/
		MouseButtonEvent(int mouseButton) : m_mouseButton(mouseButton) {};

		int m_mouseButton; //!< Float variable, mouse button
	
	public: // Public members
		//! Return the mouse button pressed (code)
		/*!
		\return A integer representing the mouse button code (if pressed)
		*/
		inline int getMouseButton() const { return m_mouseButton; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput; }

	};

	/*!
	\class MouseButtonPressedEvent
	\brief Contains variables and functions for the mouse button pressed event, inherits from class MouseButtonEvent
	*/
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public: // Public members
		//! Constructor, set mouse button
		/*!
		\param mouseButton A integer representing the mouse button code (if pressed)
		*/
		MouseButtonPressedEvent(int mouseButton) : MouseButtonEvent(mouseButton) {};
		
		//! Return the mouse button pressed (code)
		/*!
		\return A integer representing the mouse button code (if pressed)
		*/
		inline int getMouseButton() const { return m_mouseButton; } 

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::MouseButtonPressed; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::MouseButtonPressed; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput; }

	};

	/*!
	\class MouseButtonReleasedEvent
	\brief Contains variables and functions for the mouse button released event, inherits from class MouseButtonEvent
	*/
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public: // Public members
		//! Constructor, set mouse button
		/*!
		\param mouseButton A integer representing the mouse button code (if released)
		*/
		MouseButtonReleasedEvent(int mouseButton) : MouseButtonEvent(mouseButton) {};

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::MouseButtonReleased; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::MouseButtonReleased; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput; }
	};
};