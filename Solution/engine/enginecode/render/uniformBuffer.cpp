/** \file uniformBuffer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "render/renderAPI.h" // Include renderAPI.h file

#include "systems/log.h" // Include log.h file

#include "render/uniformBuffer.h" // Include uniformBuffer.h file

#include "platform/opengl/OpenGLUniformBuffer.h" // Include OpenGLBasicRenderer.h file

namespace Engine // Engine namespace
{
	UniformBuffer * UniformBuffer::Create(unsigned int size, UniformBufferLayout& layout) // Create a uniform buffer object instance
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
			return new OpenGLUniformBuffer(size, layout); // Return a OpenGLUniformBuffer class instance, passing the buffer size and the buffer layout
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

	UniformBuffer * UniformBuffer::Create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout) // Create a uniform buffer object instance
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
			return new OpenGLUniformBuffer(size, rangeStart, rangeEnd, layout); // Return a OpenGLUniformBuffer class instance, passing the buffer size, starting buffer offset, ending buffer offset and the buffer layout
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
