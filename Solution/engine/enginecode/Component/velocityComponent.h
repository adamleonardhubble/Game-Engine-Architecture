/** \file velocityComponent.h
*/

#pragma once // Compile once

#include "Component/component.h" // Include component.h file

#include <glm/glm.hpp> // Include glm support

#include <glm/gtx/transform.hpp> // Include glm transformation support

#include <glm/gtx/quaternion.hpp> // Include glm quaternion support

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class VelocityComponent
	\brief Class for game object velocity components. Provides means
	* for initialisation of game object velocities, updating game object 
	* velocities and recieving and sending component-based messages. 
	* Inherits from Component class.
	*/
	class VelocityComponent : public Component
	{
	private: // Private members
		glm::vec3 m_linear; //!< Vector(floats), representing the linear velocity
		glm::vec3 m_angular; //!< Vector(floats), representing the angular velocity

	public: // Public members
		//! Constructor, set the velocity of an object, passing the linear and angular velocities
		VelocityComponent(glm::vec3 linear, glm::vec3 angular) : m_linear(linear), m_angular(angular) {};

		//! Recieve a component-based message, passing the message
		/*!
		\param message A reference to the ComponentMessage class
		*/
		void recieveMessage(const ComponentMessage& message) override
		{
			switch (message.m_msgType) //!< Switch case statement, the message type of the passed message
			{
			case ComponentMessageType::VelocitySetLinear: //!< If the message type is the 'VelocitySetLinear' type, do the following
			{
				glm::vec3 linear = std::any_cast<glm::vec3>(message.m_msgData); //!< Create a vector(floats) and set it to the passed message data, casted into a vector(floats)
				m_linear = linear; //!< Set 'm_linear' to linear

				return; //!< Return
			}
			case ComponentMessageType::VelocitySetAngular: //!< If the message type is the 'VelocitySetAngular' type, do the following
			{
				glm::vec3 angular = std::any_cast<glm::vec3>(message.m_msgData); //!< Create a vector(floats) and set it to the passed message data, casted into a vector(floats)
				m_angular = angular; //!< Set 'm_angular' to angular

				return; //!< Return
			}
			}
		}

		//! Update the velocity component, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		void onUpdate(float timestep) override
		{
			std::pair<glm::vec3, glm::vec3> data(m_linear * timestep, m_angular * timestep); //!< Create a variable representing the integral velocity of an object in respect of time passing (position)
			ComponentMessage message(ComponentMessageType::PositionIntegrate, std::any(data)); //!< Create a message instance, set the message type and pass the associated data
			sendMessage(message); //!< Send a PositionIntegrate component message, per passing frame
		}

	};
}