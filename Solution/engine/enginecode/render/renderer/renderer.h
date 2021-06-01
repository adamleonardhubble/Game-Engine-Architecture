/** \file renderer.h
*/

#pragma once // Compile once

#include <memory> // Include memory support

#include <map> // Include map support

#include <unordered_map> // Include unordered map support

#include "render/renderer/renderCommand.h" // Include renderCommand.h file

#include "render/material.h" // Include memory.h file

#include "render/uniformBuffer.h" // Include uniformBuffer.h file

namespace Engine //!< \namespace Engine namespace
{
	using SceneData = std::unordered_map<std::shared_ptr<UniformBuffer>, std::vector<void*>>; //!< Create a unordered map, storing pointers to the 'UniformBuffer' class and a vector container, of void pointers (data)

	using PerDrawData = std::map<std::string, void *>; //!< Create a ordered map, storing strings representing the name of a material and void pointers representing the data for each material

	/**
	\class Renderer
	\brief Interface class for all render API renderers. Provides means for
	* initialisation and creation of renderers. Able to submit materials to
	* draw, draw everything to a renderer scene (frame) and call render commands
	*/
	class Renderer 
	{
	public: // Public members
		//! Invoke a render command
		/*!
		\param command A pointer to the RenderCommand class
		*/
		virtual void actionCommand(RenderCommand * command) = 0;

		//! Prepare a scene (frame) for submission
		/*!
		\param sceneData A reference to the SceneData class
		*/
		virtual void beginScene(const SceneData& sceneData) = 0;

		virtual void endScene() = 0; //!< End of a scene (frame)

		//! Submit a material for drawing
		/*!
		\param mateial A reference to a Material class pointer
		*/
		virtual void submit(const std::shared_ptr<Material>& material) = 0;

		virtual void flush() = 0; //!< Draw everything

		static Renderer * createSimple3D(); //!< A raw pointer function to the Renderer class (super simple renderer)

		static Renderer * createBasic3D(); //!< A raw pointer function to the Renderer class (basic renderer)

		static Renderer * createTextRenderer(); //!< A raw pointer function to the Renderer class (text renderer)

	};
}