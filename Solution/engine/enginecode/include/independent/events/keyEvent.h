/** \file keyEvent.h
*/

#pragma once // Compile once

#include "events/event.h" // Include event.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class KeyEvent
	\brief Contains variables and functions for the key event, inherits from class Event
	*/
	class KeyEvent : public Event
	{
	protected: // Protected members
		//! Constructor, set key typed (code)
		/*!
		\param keycode A integer representing the key code (if typed)
		*/
		KeyEvent(int keycode) : m_keyCode(keycode) {};

		int m_keyCode; //!< Integer variable, key code
	
	public: // Public members
		//! Return the key typed (code)
		/*!
		\return A integer representing the key code (if pressed)
		*/
		inline int getKeyCode() const { return m_keyCode; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }
	
	};

	/*!
	\class KeyTypedEvent
	\brief Contains variables and functions for the key typed event, inherits from class KeyEvent
	*/
	class KeyTypedEvent : public KeyEvent
	{
	public: // Public members
		//! Constructor, set key typed (code)
		/*!
		\param keycode A integer representing the key code (if pressed)
		*/
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {};

		//! Return the key typed (code)
		/*!
		\return A integer representing the key code (if typed)
		*/
		inline int getKeyTyped() const { return m_keyCode; }

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::KeyTyped; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::KeyTyped; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

	};
	
	/*!
	\class KeyPressedEvent
	\brief Contains variables and functions for the key pressed event, inherits from class KeyEvent
	*/
	class KeyPressedEvent : public KeyEvent
	{
	private: // Private members
		int m_keyRepeatCount; //!< Integer variable, key repeat count

	public: // Public members
		//! Constructor, set key pressed (code) and repeat count of key event
		/*!
		\param keycode A integer representing the key code (if pressed)
		\param keyRepeat A integer representing the key code repeat count 
		*/
		KeyPressedEvent(int keycode, int keyRepeat) : KeyEvent(keycode), m_keyRepeatCount(keyRepeat) {};

		//! Return the key pressed repeat count (code)
		/*!
		\return A integer representing the key code repeat count (if pressed)
		*/
		inline int getKeyRepeatCount() const { return m_keyRepeatCount; }

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::KeyPressed; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::KeyPressed; } 

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

	};

	/*!
	\class KeyReleasedEvent
	\brief Contains variables and functions for the key released event, inherits from class KeyEvent
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	public: // Public members
		//! Constructor, set key typed (released)
		/*!
		\param keycode A integer representing the key code (if released)
		*/
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {};

		//! Return the event type (static)
		/*!
		\return A integer representing the event type
		*/
		static EventType getStaticType() { return EventType::KeyReleased; }

		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		EventType getEventType() const override { return EventType::KeyReleased; }

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

	};
}
