/** \file UIlayer.h
*/

#pragma once // Compile once

#include "../independent/core/layer.h" // Include layer.h file

#include "../independent/events/event.h" // Include event.h file

#include "../independent/events/keyEvent.h" // Include keyEvent.h file

#include "engine.h" // Include engine.h file

	/**
	\class UILayer
	\brief Class for the user interface type layer instance. Provides means
	* for initialisation and creation of the user interface layer, updating 
	* the user interface layer and dispatching user interface layer controlled 
	* events. Inherits from Layer class.
	*/
	class UILayer : public Engine::Layer
	{
	private: // Private members
		std::shared_ptr<Engine::UniformBuffer> m_pMatricesUBO; //!< Shared pointer, of type UniformBuffer class (pointer to UniformBuffer class) - matrices ubo (shader uniform block)

		std::shared_ptr<Engine::CameraController> m_pOrthographicCamera; //!< Shared pointer, of type CameraController class (pointer to CameraController class) - 2D camera (UI)
		std::shared_ptr<Engine::Renderer> m_pTextRenderer; //!< Shared pointer, of type Renderer class (pointer to Renderer class) - text renderer

		std::shared_ptr<Engine::Shader> m_pTextShader; //!< Shared pointer, of type Shader class (pointer to Shader class) - glyph texture (Letter)
		std::shared_ptr<Engine::Texture> m_pGlyphTexture; //!< Shared pointer, of type Texture class (pointer to Texture class) - glyph texture (Letter)
		std::shared_ptr<Engine::VertexArray> m_pTextVAO; //!< Shared pointer, of type VertexArray class (pointer to VertexArray class) - glyph texture (Letter)
		std::shared_ptr<Engine::Material> m_pTextMaterial; //!< Shared pointer, of type Material class (pointer to Material class) - glyph texture (Letter)

		Engine::SceneData sceneData; //!< SceneData unordered map object

		bool m_toggleCamera = true; //!< Boolean variable, determine whether the orthographic camera is being updated (controller active)

	public: // Public members
		//! Constructor, set the UI layer name
		/*!
		\param name A string representing the name of a layer instance
		*/
		UILayer(const std::string& name = "Layer") : Layer(name) {};

		void onAttach() override; //!< Intialise the UI layer instance, on attach

		void onDetach() override; //!< Unset the UI layer instance variables, on detach

		//! Update the UI layer instance, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		void onUpdate(float timestep) override; 

		//! Dispatch UI layer controlled events
		/*!
		\param event A reference to the Event class
		*/
		void onEvent(Engine::Event& event) override;

		//! Pressed key event
		/*!
		\param event A reference to the KeyPressedEvent class
		\return A boolean which identifies the event success
		*/
		bool onKeyPressedEvent(Engine::KeyPressedEvent& event);
	};
