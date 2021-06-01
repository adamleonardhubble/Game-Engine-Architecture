/** \file OpenGLRenderCommand.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include <glad/glad.h> // Include glad.h file

#include "platform/opengl/renderer/OpenGLRenderCommand.h" // Include OpenGLRenderCommand.h file

namespace Engine // Engine namespace
{
	void OpenGLClearDepthColourBufferCommand::action() // Clear the colour writing buffers and depth buffers render command
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear colour writing and depth buffers
	}

	void OpenGLSetClearColourCommand::action() // Set the colour of the window clear colour render command
	{
		glClearColor(m_r, m_g, m_b, m_a); // Set clear colour to the passed clear colour command values in the constructor of the class
	}

	void OpenGLSetDepthTestLessCommand::action() // Set the status of the depth testing less render command
	{
		if (m_depthTestLessEnabled == true) // If 'm_depthTestLessEnabled' is 'true', do the following
		{
			glEnable(GL_DEPTH_TEST); // Enable depth testing
			glDepthFunc(GL_LESS); // Set the depth testing function to depth testing less (discards all the fragments that have a depth value higher than or equal to the current depth buffer's value)
		}
		else // Else if 'm_depthTestLessEnabled' is 'false', do the following
		{
			glDisable(GL_DEPTH_TEST); // Disable depth testing
		}
	}

	void OpenGLSetBackfaceCullingCommand::action() // Set the status of the backface culling render command
	{
		if (m_backfaceCullingEnabled == true) // If 'm_backfaceCulling' is 'true', do the following
		{
			glEnable(GL_CULL_FACE); // Enable geometry face culling
			glCullFace(GL_BACK); // Set the face culling to the back faces of geometry (relative to the viewport/ camera position)
		}
		else // Else if 'm_backfaceCulling' is 'false', do the following
		{
			glDisable(GL_CULL_FACE); // Disable geometry face culling
		}
	}

	void OpenGLClearColourBufferCommand::action() // Set the status of the clear colour buffer render command
	{
		glClear(GL_COLOR_BUFFER_BIT); // Clear colour writing buffers
	}

	void OpenGLSetOneMinusAlphaBlending::action() // Set the status of the alpha blending render command
	{
		if (m_alphaBlendingEnabled == true) // If 'm_alphaBlendingEnabled' is 'true', do the following
		{
			glEnable(GL_BLEND); // Enable depth testing
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable alpha blending
		}
		else // Else if 'm_alphaBlendingEnabled' is 'false', do the following
		{
			glDisable(GL_BLEND); // Disable alpha blending
		}
	}
}