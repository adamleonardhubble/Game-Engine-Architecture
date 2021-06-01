/** \file component.h
*/

#pragma once // Compile once

#include "events/event.h" // Include event.h file

#include "Component/componentMessage.h" // Include componentMessage.h file

namespace Engine //!< \namespace Engine namespace
{
	class GameObject; //!< Forward declare the GameObject class

	/**
	\class Component
	\brief Class for game object components. Provides means
	* for initialisation and creation of game object components,
	* updating game object components, dispatching component controlled
	* events, sending and recieving component-based messages.
	*/
	class Component
	{
	protected: // Protected members
		GameObject * m_owner = nullptr; //!< Raw pointer, of type GameObject class (pointer to GameObject class) set to 'NULL'

		//! Send a component-based message, passing the message
		/*!
		\param message A reference to the ComponentMessage class
		*/
		virtual void sendMessage(const ComponentMessage& message)
		{

		}

	public: // Public members
		//! Set the owner of a component, on attach
		/*!
		\param owner A raw pointer appointed to the GameObject class
		*/
		virtual void onAttach(GameObject * owner) { m_owner = owner; }

		virtual void onDetach() { m_owner = nullptr; } //!< Unset the owner of a component, on detach

		//! Update a component, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		virtual void onUpdate(float timestep) {};

		//! Dispatch component controlled events
		/*!
		\param e A reference to the Event class
		*/
		virtual void onEvent(Event& e) {};

		//! Recieve a component-based message, passing the message
		/*!
		\param message A reference to the ComponentMessage class
		*/
		virtual void recieveMessage(const ComponentMessage& message) = 0;

	};

	/**
	\class GameObject
	\brief Class for game objects. Provides means
	* for initialisation and creation of game objects, updating
	* game objects, adding and removing game objects to a game object
	* instance container, dispatching game object controlled events
	* and retrieving game object components.
	*/
	class GameObject
	{
	protected: // Protected members
		std::vector<std::shared_ptr<Component>> m_components; //!< Vector container, containing shared pointers to the Component class

	public: // Public members
		//! Update a game object, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		void onUpdate(float timestep)
		{

		}

		//! Dispatch game object controlled events
		/*!
		\param e A reference to the Event class
		*/
		void onEvent(Event& e)
		{
			Engine::EventDispatcher dispatcher(e); // Create an 'EventDispatcher' class object, passing an event type

			//---> Mouse button events
		}

		//! Add a component instance to an objects component container
		/*!
		\param component A shared pointer appointed to the Component class
		*/
		void addComponent(const std::shared_ptr<Component>& component)
		{
			m_components.push_back(component); //!< Push the passed component onto the game objects component container
		}

		//! Remove a component instance from an objects component container
		/*!
		\param iterator A vector container iterator of component instances
		*/
		void removeComponent(std::vector<std::shared_ptr<Component>>::iterator iterator)
		{
			m_components.erase(iterator); //!< Erase a game objects component from the passed position of the component in the container
		}

		//! Return an objects component
		/*!
		\return A component instance stored in the component container
		*/
		template<typename G>
		std::vector<std::shared_ptr<Component>>::iterator getComponent()
		{
			auto result = m_components.end(); //!< Set 'result' to the last component instance in the objects component container

			for (auto it = m_components.begin(); it != m_components.end(); ++it) //!< For all component instances at the beggining to the end of the objects component container, do the following
			{
				if (typeid(decltype(*(it->get()))).hash_code() == typeid(G).hash_code()) //!< If the current components type matches one of the objects component types, do the following
				{
					return it; //!< Return 'it' (current object component in the iteration)
				} 
			}
			return result; //!< Return 'result' (last component in the objects component container)
		}

		//! Return the first element in the objects component vector container
		/*!
		\return A shared pointer to the Component class, the first element in the container
		*/
		inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); } 

		//! Return the last element in the objects component vector container
		/*!
		\return A shared pointer to the Component class, the last element in the container
		*/
		inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }

	};
}