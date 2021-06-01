/** \file OpenGLTextRenderer.h
*/

#pragma once // Compile once

#include "render/renderer/renderer.h" // Include renderer.h file

#include "render/renderer/renderCommand.h" // Include renderCommand.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLTextRenderer
	\brief Class for OpenGL API specific text renderers. Provides
	* means for initialisation and creation of OpenGL textures. Inherits
	* from Renderer class.
	*/
	class OpenGLTextRenderer : public Renderer
	{
	private: // Private members

	public: // Public members
		//! Invoke a render command
		/*!
		\param command A pointer to the RenderCommand class
		*/
		void actionCommand(RenderCommand * command) override;

		//! Prepare a scene (frame) for submission
		/*!
		\param sceneData A reference to the SceneData class
		*/
		void beginScene(const SceneData& sceneData) {};

		void endScene() override {}; //!< End of a scene (frame)

		//! Submit a material instance for drawing
		/*!
		\param mateial A reference to a Material class pointer
		*/
		void submit(const std::shared_ptr<Material>& material) override;

		void flush() override {}; //!< Draw everything

	};
}