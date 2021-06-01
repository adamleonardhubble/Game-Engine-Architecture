/** \file materialComponent.h
*/

#pragma once // Compile once

#include "Component/component.h" // Include component.h file

#include "render/material.h" // Include material.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class MaterialComponent
	\brief Class for game object materials. Provides means
	* for initialisation and creation of game object materials, 
	* retrieving game object material instances and recieving
	* component-based messages.
	* Inherits from Component class.
	*/
	class MaterialComponent : public Component
	{
	private: // Private members
		std::shared_ptr<Material> m_pMaterial; //!< Shared pointer, of type Material class (pointer to Material class)

	public: // Public members
		//! Constructor, set the material of an object, passing a material pointer instance
		/*!
		\param material A shared pointer appointed to the Material class
		*/
		MaterialComponent(const std::shared_ptr<Material>& material) : m_pMaterial(material) {};

		//! Return a material instance
		/*!
		\return A shared pointer appointed to the material class
		*/
		inline std::shared_ptr<Material> getMaterial() { return m_pMaterial; }

		//! Recieve a component-based message, passing the message
		/*!
		\param message A reference to the ComponentMessage class
		*/
		void recieveMessage(const ComponentMessage& message) override
		{
			switch (message.m_msgType) //!< Switch case statement, the message type of the passed message
			{
			case ComponentMessageType::UniformSet: //!< If the message type is the 'UniformSet' type, do the following
			{
				std::pair<std::string, void *> data = std::any_cast<std::pair<std::string, void *>>(message.m_msgData); //!< Create a pair of strings and void pointers and set it to the passed message data, casted into strings and void pointers
				m_pMaterial->setDataElement(data.first, data.second); //!< Upload uniform variable data, set uniform variable name and its associated data

				return; //!< Return
			}
			}
		}

	};
}