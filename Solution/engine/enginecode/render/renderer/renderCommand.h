/** \file renderCommand.h
*/

#pragma once // Compile once

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class RenderCommand
	\brief Interface class for all render API render commands. Provides means for
	* initialisation and creation of render commands. Able to clear depth buffer colour,
	* set window clear colour and clear the window, set depth testing less for geometry 
	* fragments, set face culling of geometry facing away from the camera (back facing),
	* clear colour writing buffers and enables alpha blending between geometry
	*/
	class RenderCommand
	{
	public: // Public members
		virtual void action() = 0; //!< Invoke a render command

		static RenderCommand * clearDepthColourBufferCommand(); //!< Create a clear depth colour buffer renderer command instance

		static RenderCommand * setClearColourCommand(float r, float g, float b, float a); //!< Create a clear window colour renderer command instance, passing the RGBA values of the colour

		static RenderCommand * setDepthTestLessCommand(bool enabled); //!< Create a depth test less renderer command instance, passing a boolean determining its enabled status

		static RenderCommand * setBackfaceCullingCommand(bool enabled); //!< Create a backface culling renderer command instance, passing a boolean determining its enabled status

		static RenderCommand * clearColourBufferCommand(); //!< Create a colour buffer renderer command instance
		
		static RenderCommand * setOneMinusAlphaBlending(bool enabled); //!< Create a alpha blending renderer command instance

	};
}