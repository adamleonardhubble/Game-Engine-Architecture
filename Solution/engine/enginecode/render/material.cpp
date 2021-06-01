/** \file material.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "systems/log.h" // Include log.h file

#include "render/renderAPI.h" // Include renderAPI.h file

#include "render/material.h" // Include material.h file

#include "platform/opengl/OpenGLMaterial.h" // Include OpenGLMaterial.h file

namespace Engine // Engine namespace
{
	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO) // Create a material instance, passing the shader and vertex array object pointers
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
			return new OpenGLMaterial(shader, VAO); // Return a new instance of a OpenGL material, passing the shader and vertex array object pointers
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

	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO) // Create a material instance, passing the shader and vertex buffer object pointers
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
			ENGINE_CRITICAL("OpenGL vertex array objects only support geometry data"); // Output type 'critical' to logger console window, output vertex array objects only support geometry data
			return nullptr; // Return 'nullptr', OpenGL does not incorporate such graphics content in vertex buffer (only in VAO) 
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