/** \file event.h
*/

#include <functional> // Include functional library

#pragma once // Compile once

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class EventType
	\brief An enumerator type class, containing enumerators of events
	*/
	enum class EventType
	{
		None = 0, //!< None
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, //!< Window events
		KeyPressed, KeyReleased, KeyTyped, //!< Key events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled //!< Mouse events
	};

	/*!
	\enum EventCategory
	\brief An enumerator container, holding enumerators of event categories that are
	* bit shifted. Bit shift provides a unique pattern for each category.
	*/
	enum EventCategory
	{
		None = 0, //!< None
		EventCategoryWindow =		1 << 0, //!< 00000001
		EventCategoryInput =		1 << 1, //!< 00000010
		EventCategoryKeyboard =		1 << 2, //!< 00000100
		EventCategoryMouse =		1 << 3, //!< 00001000
		EventCategoryMouseButton =	1 << 4 //!< 00010000
	};

	/*!
	\class Event
	\brief A base class, containing variables and functions for all of the events
	*/
	class Event
	{
	private: // Private members
		bool m_bHandled = false; //!< Boolean variable, determine if event has been handled

	public: // Public members
		//! Return the event type
		/*!
		\return A integer representing the event type
		*/
		virtual EventType getEventType() const = 0;

		//! Return event category flags
		/*!
		\return Integer variables representing the categories of the event (enums)
		*/
		virtual int getCategoryFlags() const = 0;

		//! Determine whether the event has been handled or not
		/*!
		\return A boolean stating the event handled status
		*/
		inline bool bEventHandled() const { return m_bHandled; }

		//! Handle the event (set variable)
		/*!
		\param isHandled A boolean stating the event handled status
		*/
		inline void eventHandle(bool isHandled) { m_bHandled = isHandled; }

		//! Compare event category with an events category flag(s), determining whether the event is in the correct category
		/*!
		\param category A reference to the EventCategory enum class
		*/
		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }
	};

	/*!
	\class EventDispatcher
	\brief Contains variables and functions for the event dispatcher, used to handle passed events
	*/
	class EventDispatcher
	{
		//! Set event passing function
		/*!
		\param T A reference to an event class type
		\return A boolean (<bool>) for any given type of 'event' (T&) class passed, when handled (handled or not handled)
		*/
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

	private: // Private members
		Event& m_Event; //!< Reference, Event class reference (store the event passed to dispatcher)

	public: // Public members
		//! Constructor, sets the event passed to the dispatcher
		/*!
		\param event A reference to the Event class being dispatched
		*/
		EventDispatcher(Event& event) : m_Event(event) {};

		//! Dispatch events
		/*!
		\param func A function specific to an event type 
		\return A boolean to identify whether the passed event function was handled or not handled
		*/
		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_Event.getEventType() == T::getStaticType()) //!< If event (function) trying to be dispatched matches the event type of type T, do the following
			{
				m_Event.eventHandle(func(*((T*)&m_Event))); //!< Handle the passed event function

				return true; //!< Return 'true' (event handled)
			}

			return false; //!< Return 'false' (event not handled)
		}
	};
}
