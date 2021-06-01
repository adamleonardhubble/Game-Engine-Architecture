/** \file componentMessage.h
*/

#pragma once // Compile once

#include <any> // Include any support

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class ComponentMessageType
	\brief An enumerator type class, containing enumerators of message types
	*/
	enum class ComponentMessageType
	{
		None = 0, //!< None
		PositionIntegrate, PositionSet, RelativePositionSet, //!< Position types
		VelocityIntegrate, VelocitySetLinear, VelocitySetAngular,
		AccelerationSet, //!< Acceleration type
		KeyPressed, KeyReleased, MouseButton, MouseScroll, MouseMoved, //!< Input types
		UniformSet, TextureSet //!< Uniform types
	};

	/**
	\class ComponentMessage
	\brief Class for component messages. Provides means
	* for initialisation of component messages.
	*/
	class ComponentMessage
	{
	public: // Public members
		//! Constructor, set the message type and associated data
		/*!
		\param type A ComponentMessageType class object instance
		\param data An object that stores message data of any type
		*/
		ComponentMessage(ComponentMessageType type, std::any data) : m_msgType(type), m_msgData(data) {};

		ComponentMessageType m_msgType; //!< Message type, a ComponentMessage class object

		std::any m_msgData; //!< Data associated with the message 
	};
}
