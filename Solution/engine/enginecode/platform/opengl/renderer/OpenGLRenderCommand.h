/** \file OpenGLRenderCommand.h
*/

#pragma once // Compile once

#include "render/renderer/renderCommand.h" // Include RenderCommand.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLClearDepthColourBufferCommand
	\brief Class for OpenGL API specific depth colour buffer render 
	* command. Provides means for clearing colour writing buffers
	* and depth buffers. Inherits from RenderCommand class.
	*/
	class OpenGLClearDepthColourBufferCommand : public RenderCommand
	{
	private: // Private members

	public: // Public members
		//! Default constructor
		OpenGLClearDepthColourBufferCommand() {};

		void action() override; //!< Clear the colour writing buffers and depth buffers render command

	};

	/**
	\class OpenGLSetClearColourCommand
	\brief Class for OpenGL API specific clear colour render
	* command. Provides means for setting and clearing the window
	* with the given clear colour. Inherits from RenderCommand class.
	*/
	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private: // Private members
		float m_r; //!< Float, red colour value of the window clear colour
		float m_g; //!< Float, green colour value of the window clear colour
		float m_b; //!< Float, blue colour value of the window clear colour
		float m_a; //!< Float, alpha (opaqueness) colour value of the window clear colour

	public: // Public members
		//! Constructor, set OpenGL window clear colour
		/*!
		\param r A float representing the red value of the window clear RGBA colour
		\param g A float representing the green value of the window clear RGBA colour
		\param b A float representing the blue value of the window clear RGBA colour
		\param a A float representing the alpha (opaqueness) value of the window clear RGBA colour
		*/
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};

		void action() override; //!< Set the colour of the window clear colour render command

	};

	/**
	\class OpenGLSetDepthTestLessCommand
	\brief Class for OpenGL API specific depth testing less render
	* command. Provides means for enabling depth testing and setting
	* the depth testing type. Inherits from RenderCommand class.
	*/
	class OpenGLSetDepthTestLessCommand : public RenderCommand
	{
	private: // Private members
		bool m_depthTestLessEnabled; //!< Boolean variable, determine whether depth testing less is enabled or disabled

	public: // Public members
		//! Constructor, set OpenGL depth testing less activeness
		/*!
		\param enabled A boolean representing the active status of depth testing less
		*/
		OpenGLSetDepthTestLessCommand(bool enabled) : m_depthTestLessEnabled(enabled) {};

		void action() override; //!< Set the status of the depth testing less render command

	};

	/**
	\class OpenGLSetBackfaceCullingCommand
	\brief Class for OpenGL API specific geometry face culling render
	* command. Provides means for enabling geometry face culling and
	* the face culling type. Inherits from RenderCommand class.
	*/
	class OpenGLSetBackfaceCullingCommand : public RenderCommand
	{
	private: // Private members
		bool m_backfaceCullingEnabled; //!< Boolean variable, determine whether geometry face culling is enabled or disabled

	public: // Public members
		//! Constructor, set OpenGL geometry backface culling activeness
		/*!
		\param enabled A boolean representing the active status of geometry backface culling
		*/
		OpenGLSetBackfaceCullingCommand(bool enabled) : m_backfaceCullingEnabled(enabled) {};

		void action() override; //!< Set the status of the backface culling render command

	};

	/**
	\class OpenGLClearColourBufferCommand
	\brief Class for OpenGL API specific colour buffer render
	* command. Provides means for clearing colour writing buffers. 
	* Inherits from RenderCommand class.
	*/
	class OpenGLClearColourBufferCommand : public RenderCommand
	{
	private: // Private members

	public: // Public members
		//! Default constructor
		OpenGLClearColourBufferCommand() {};

		void action() override; //!< Clear the colour writing buffers render command

	};

	/**
	\class OpenGLSetOneMinusAlphaBlending
	\brief Class for OpenGL API specific geometry alpha blending render
	* command. Provides means for enabling geometry alpha blending.
	* Inherits from RenderCommand class.
	*/
	class OpenGLSetOneMinusAlphaBlending : public RenderCommand
	{
	private: // Private members
		bool m_alphaBlendingEnabled; //!< Boolean variable, determine whether geometry alpha blending is enabled or disabled

	public: // Public members
		//! Constructor, set OpenGL geometry alpha blending activeness
		/*!
		\param enabled A boolean representing the active status of geometry alpha blending
		*/
		OpenGLSetOneMinusAlphaBlending(bool enabled) : m_alphaBlendingEnabled(enabled) {};

		void action() override; //!< Set the status of the alpha blending render command

	};
}

