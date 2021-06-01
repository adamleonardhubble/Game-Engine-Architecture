/** \file OpenGLSuperSimpleRenderer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include <glad/glad.h> // Include glad.h file

#include "platform/opengl/renderer/OpenGLSuperSimpleRenderer.h" // Include OpenGLSuperSimpleRenderer.h file

namespace Engine // Engine namespace
{
	void OpenGLSuperSimpleRenderer::actionCommand(RenderCommand * command) // Invoke a render command
	{
		command->action(); // Invoke the passed render command, fetch render command function from the specified OpenGLRenderCommand class instances specified in application body
		delete command; // Delete the render command after the render command has been invoked 
	}

	void OpenGLSuperSimpleRenderer::submit(const std::shared_ptr<Material>& material) // Submit a material instance for drawing
	{
		auto Shader = material->getShader(); // Return and store the shader instance
		Shader->Bind(); // Bind the shader object to a rendering program instance

		auto Geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry()); // Return and store the vertex array object (geometry)
		Geometry->Bind(); // Bind the vertex array object

		auto uniformData = material->getData(); // Return and store the uniform per draw data stored in the map
		
		for (auto dataPair : uniformData) // For every pair (uniform name and its associated data) in the map, do the following
		{
			Shader->uploadData(dataPair.first, dataPair.second); // Upload the uniform variable data (create uniform variable for each type dispatched)
		}

		glDrawElements(GL_TRIANGLES, Geometry->getCount(), GL_UNSIGNED_INT, nullptr); // Draw the geometry (issue a draw call for the preceeding material)
	}
}