/** \file vertexBuffer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "render/renderAPI.h" // Include renderAPI.h file
#include "render/vertexBuffer.h" // Include vertexBuffer.h file

#include "platform/opengl/OpenGLVertexBuffer.h" // Include OpenGLVertexBuffer.h file

#include "systems/log.h" // Include log.h file

namespace Engine // Engine namespace
{
	VertexBuffer * VertexBuffer::Create(float * vertices, unsigned int count, BufferLayout& bufferLayout) // Create a renderer vertex buffer
	{
		switch (RenderAPI::getAPI()) // Switch case statement, return the current renderer API
		{
		case RenderAPI::API::None: // If there is renderer API currently set, do the following
		{
			ENGINE_CRITICAL("Lack of graphics API not supported"); // Output type 'critical' to logger console window, output the lack of support for no set API
			break; // Break from the switch case statement
		}
		case RenderAPI::API::OpenGL: // If the renderer API currently set is 'OpenGL', do the following
		{
			return new OpenGLVertexBuffer(vertices, count, bufferLayout); // Return a new instance of an OpenGL API vertex buffer, passing the set vertex buffer data 
			break; // Break from the switch case statement
		}
		case RenderAPI::API::Direct3D: // If the renderer API currently set is 'Direct3D', do the following
		{
			ENGINE_CRITICAL("Direct3D not supported"); // Output type 'critical' to logger console window, output the lack of support for Direct3D API (currently)
			break; // Break from the switch case statement
		}
		default: // If the renderer API currently set is none of the API specified, do the following (check for missed implementation)
		{
			ENGINE_CRITICAL("Unknown graphics API"); // Output type 'critical' to logger console window, output the API is not known (not specified for use)
		}
		}
	}
}

