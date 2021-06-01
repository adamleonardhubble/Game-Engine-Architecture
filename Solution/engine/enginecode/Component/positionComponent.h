/** \file positionComponent.h
*/

#pragma once // Compile once

#include "Component/component.h" // Include component.h file

#include <glm/glm.hpp> // Include glm support

#include <glm/gtx/transform.hpp> // Include glm transformation support

#include <glm/gtx/quaternion.hpp> // Include glm quaternion support

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class PositionComponent
	\brief Class for game object position components. Provides means
	* for initialisation of game object positioning, recalculating
	* and updating game object positioning, retrieving game object
	* transformations and recieving and sending component-based 
	* messages. Inherits from Component class.
	*/
	class PositionComponent : public Component
	{
	private: // Private members
		glm::mat4 m_model; //!< Matrix, representing the model matrix
		glm::mat4 m_translation; //!< Natrix, representing the translation matrix
		glm::mat4 m_rotation; //!< Matrix, representing the rotation matrix
		glm::mat4 m_scale; //!< Matrix, representing the scale matrix

		glm::vec3 m_translateVector; //!< Vector(floats), representing the translation vector
		glm::vec3 m_rotateVector; //!< Vector(floats), representing the rotation vector
		glm::vec3 m_scaleVector; //!< Vector(floats), representing the scale vector

		inline void calculateModel() //!< Calculate the model matrices (or recalculate)
		{
			m_translation = glm::translate(glm::mat4(1.0f), m_translateVector); //!< Update and set the new translation matrix of the model
			m_rotation = glm::toMat4(glm::quat(m_rotateVector)); //!< Update and set the new rotation matrix of the model
			m_scale = glm::scale(m_scaleVector); //!< Update and set the new scale matrix of the model
			m_model = m_translation * m_rotation * m_scale; //!< Update and set the new model matrix
		}

	public: // Public members
		//! Constructor, set the position of an object, passing the translation, rotation and scale vectors
		/*!
		\param translate A Vector(floats) representing the translation vector
		\param rotate A Vector(floats) representing the rotation vector
		\param scale A Vector(floats) representing the scale vector
		*/
		PositionComponent(glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale) :
			m_translateVector(translate), m_rotateVector(rotate), m_scaleVector(scale), m_model(glm::mat4(1.0f))
		{
			m_rotateVector.x = glm::radians(m_rotateVector.x); //!< Set the rotation vector in the 'X' axis, to the rotation vector in the 'X' axis converted into radians
			m_rotateVector.y = glm::radians(m_rotateVector.y); //!< Set the rotation vector in the 'Y' axis, to the rotation vector in the 'Y' axis converted into radians
			m_rotateVector.z = glm::radians(m_rotateVector.z); //!< Set the rotation vector in the 'Z' axis, to the rotation vector in the 'Z' axis converted into radians
			
			calculateModel(); //!< Call function, recalculate the model matrices
		}

		//! Return the transformation matrix of an object
		/*!
		\return A shared pointer appointed to a four dimensional matrix
		*/
		inline std::shared_ptr<glm::mat4> getTransform() { return std::make_shared<glm::mat4>(m_model); }

		//! Recieve a component-based message, passing the message
		/*!
		\param message A reference to the ComponentMessage class
		*/
		void recieveMessage(const ComponentMessage& message) override
		{
			switch (message.m_msgType) //!< Switch case statement, the message type of the passed message
			{
			case ComponentMessageType::PositionSet: //!< If the message type is the 'PositionSet' type, do the following
			{
				glm::vec3 position = std::any_cast<glm::vec3>(message.m_msgData); //!< Create a vector(floats) and set it to the passed message data, casted into a vector(floats)
				m_translateVector = position; //!< Set 'm_translationVector' to position

				calculateModel(); //!< Call function, recalculate the model matrices

				return; //!< Return
			}
			case ComponentMessageType::PositionIntegrate: //!< If the message type is the 'PositionIntegrate' type, do the following
			{
				std::pair<glm::vec3, glm::vec3> velocity = std::any_cast<std::pair<glm::vec3, glm::vec3>>(message.m_msgData); //!< Create a pair of vectors(floats) and set it to the passed message data, casted into vectors(floats)

				m_translateVector += velocity.first; //!< Set 'm_translateVector' to add and equal the linear velocity vector (all dimensions)

				m_rotateVector.x += glm::radians(velocity.second.x); //!< Set the rotation vector in the 'X' axis, to the angular velocity vector in the 'X' axis converted into radians
				m_rotateVector.y += glm::radians(velocity.second.y); //!< Set the rotation vector in the 'Y' axis, to the angular velocity vector in the 'X' axis converted into radians
				m_rotateVector.z += glm::radians(velocity.second.z); //!< Set the rotation vector in the 'Z' axis, to the angular velocity vector in the 'X' axis converted into radians

				calculateModel(); //!< Call function, recalculate the model matrices

				return; //!< Return
			}
			}
		}

		//! Update the position component, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		void onUpdate(float timestep) override
		{
			std::pair<std::string, void *> data("u_model", (void *)&m_model[0][0]); //!< Create uniform variable for an objects model
			ComponentMessage message(ComponentMessageType::UniformSet, data); //!< Create a message instance, set the message type and pass the associated data
			sendMessage(message); //!< Send a UniformSet component message, per passing frame
		}

		//! Set the owner of a component, on attach
		/*!
		\param owner A raw pointer appointed to the GameObject class
		*/
		void onAttach(GameObject * owner) override
		{
			m_owner = owner; //!< Set 'm_owner' to the passed GameObject class pointer instance

			std::pair<std::string, void *> data("u_model", (void *)&m_model[0][0]); //!< Create uniform variable for an objects model
			ComponentMessage message(ComponentMessageType::UniformSet, data); //!< Create a message instance, set the message type and pass the associated data
			sendMessage(message); //!< Send a UniformSet component message, when intialised

		}

	};
}