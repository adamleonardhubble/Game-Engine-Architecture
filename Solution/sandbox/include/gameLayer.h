/** \file gameLayer.h
*/

#pragma once // Compile once

#include "../independent/core/layer.h" // Include layer.h file

#include "../independent/events/event.h" // Include event.h file

#include "../independent/events/keyEvent.h" // Include keyEvent.h file

#include "../enginecode/Component/materialComponent.h" // Include materialComponent.h file

#include "../enginecode/Component/velocityComponent.h" // Include velocityComponent.h file

#include "../enginecode/Component/positionComponent.h" // Include positionComponent.h file

#include "engine.h" // Include engine.h file

	/**
	\class GameLayer
	\brief Class for the game type layer instance. Provides means
	* for initialisation and creation of the game layer, updating
	* the game layer and dispatching game layer controlled events. 
	* Inherits from Layer class.
	*/
	class GameLayer : public Engine::Layer
	{
	private: // Private members
		std::shared_ptr<Engine::Shader> m_pFCShader; //!< Shared pointer, of type Shader class (pointer to Shader class) - full colour cube
		std::shared_ptr<Engine::Shader> m_pTPShader; //!< Shared pointer, of type Shader class (pointer to Shader class) - textured phong cube

		std::shared_ptr<Engine::Texture> m_pLetterTexture; //!< Shared pointer, of type Texture class (pointer to Texture class) - textured phong cube (letters)
		std::shared_ptr<Engine::Texture> m_pNumberTexture; //!< Shared pointer, of type Texture class (pointer to Texture class) - textured phong cube (numbers)

		std::shared_ptr<Engine::VertexArray> m_pFCVAO; //!< Shared pointer, of type VertexArray class (pointer to VertexArray class) - full colour cube
		std::shared_ptr<Engine::VertexArray> m_pTPVAO; //!< Shared pointer, of type VertexArray class (pointer to VertexArray class) - textured phong cube

		std::shared_ptr<Engine::Material> m_pFCMaterial; //!< Shared pointer, of type Material class (pointer to Material class) - full colour cube
		std::shared_ptr<Engine::Material> m_pTPMaterial; //!< Shared pointer, of type Material class (pointer to Material class) - textured phong cube

		std::shared_ptr<Engine::UniformBuffer> m_pMatricesUBO; //!< Shared pointer, of type UniformBuffer class (pointer to UniformBuffer class) - matrices ubo (shader uniform block)
		std::shared_ptr<Engine::UniformBuffer> m_pLightsUBO; //!< Shared pointer, of type UniformBuffer class (pointer to UniformBuffer class) - lights ubo (shader uniform block)

		std::vector<std::shared_ptr<Engine::GameObject>> m_gameObjects; //!< Vector container, containing shared pointers of type GameObject class (pointers to GameObject class)
		std::vector<std::shared_ptr<Engine::MaterialComponent>> m_materials; //!< Vector container, containing shared pointers of type MaterialComponent class (pointers to MaterialComponent class)
		std::vector<std::shared_ptr<Engine::PositionComponent>> m_positions; //!< Vector container, containing shared pointers of type PositionComponent class (pointers to PositionComponent class)
		std::vector<std::shared_ptr<Engine::VelocityComponent>> m_velocities; //!< Vector container, containing shared pointers of type VelocityComponent class (pointers to VelocityComponent class)

		bool m_toggleCamera = false; //!< Boolean variable, determine whether the perspective camera is being updated (controller active)

		glm::mat4 m_FCmodel; //!< Matrix, representing the flat colour cube model matrices
		glm::mat4 m_TPmodel; //!< Matrix, representing the textured phong cube model matrices

		unsigned int m_texSlot; //!< Unsigned integer, store texture slots in the GPU

		glm::vec4 m_lightColour; //!< Vector4(floats), representing the light colour uniform variable
		glm::vec4 m_lightPosition; //!< Vector4(floats), representing the light position uniform variable
		glm::vec4 m_viewPosition; //!< Vector4(floats), representing the view position uniform variable

		Engine::SceneData sceneData; //!< SceneData unordered map object

		bool m_goingUp = false; //!< Boolean variable, determine the full colour and textured phong cubes direction of traversal
		float m_timeSummed = 10.0f; //!< Float, store the number of seconds for the cubes direction of traversal to alternate

	public: // Public members
		//! Constructor, set the game layer name
		/*!
		\param name A string representing the name of a layer instance
		*/
		GameLayer(const std::string& name = "Layer") : Layer(name) {};

		void onAttach() override; //!< Intialise the game layer instance, on attach

		void onDetach() override; //!< Unset the game layer instance variables, on detach

		//! Update the game layer instance, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		void onUpdate(float timestep) override;

		//! Dispatch game layer controlled events
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