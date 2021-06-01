/** \file layer.h
*/

#pragma once // Compile once

#include <string> // Include string support

#include "assetmanager/resourceManager.h" // Include resourceManager.h file

#include "render/renderer/renderer.h" // Include renderer.h file

#include "render/camera/cameraController.h" // Include cameraController.h file

#include "events/inputPoller.h" // Include inputPoller.h file

//#include "events/keyEvent.h"

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class Layer
	\brief Base class for all layer type instances. Provides means for
	* initialisation and creation of layers, updating layers and
	* dispatching layer controlled events.
	*/
	class Layer
	{
	protected: // Protected members
		std::string m_name; //!< String, store the name of the layer

		std::shared_ptr<Engine::ResourceManager> m_pResourceManager; //!< Shared pointer, of type ResourceManager class (pointer to ResourceManager class)

		std::shared_ptr<Engine::Renderer> m_pRenderer; //!< Shared pointer, of type Renderer class (pointer to Renderer class)

		std::shared_ptr<Engine::CameraController> m_pCameraController; //!< Shared pointer, of type CameraController class (pointer to CameraController class)

		std::shared_ptr<Layer> m_pLayer; //!< Shared pointer, of type Layer class (pointer to Layer class)

	public: // Public members
		//! Constructor, set the layer name
		/*!
		\param name A string representing the name of a layer instance
		*/
		Layer(const std::string name);

		virtual void onAttach() {}; //!< Intialise layer instance, on attach

		virtual void onDetach() {}; //!< Unset layer instance variables, on detach

		//! Update a layer instance, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		virtual void onUpdate(float timestep) {};

		//! Dispatch layer controlled events
		/*!
		\param event A reference to the Event class
		*/
		virtual void onEvent(Engine::Event& event) {};

		//! Return the name of a layer instance
		/*!
		\return A string representing the name of a layer instance
		*/
		inline const std::string& getName() const { return m_name; }

	};
}
