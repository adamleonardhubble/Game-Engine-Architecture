/** \file OpenGLBasicRenderer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include <glad/glad.h> // Include glad.h file

#include "platform/opengl/renderer/OpenGLBasicRenderer.h" // Include OpenGLBasicRenderer.h file

namespace Engine // Engine namespace
{
	void OpenGLBasicRenderer::actionCommand(RenderCommand * command) // Invoke a render command
	{
		command->action(); // Invoke the passed render command, fetch render command function from the specified OpenGLRenderCommand class instances specified in application body
		delete command; // Delete the render command after the render command has been invoked 
	}

	void OpenGLBasicRenderer::beginScene(const SceneData& sceneData) // Prepare a scene (frame) for submission
	{
		for (auto uboPair : sceneData) // For all of the pairs stored in the 'SceneData' map (projection, view and light uniforms), do the following
		{
			unsigned int elementOffset = 0; // Create an integer, store the offset between each uniform buffer element in the uniform buffer layout
			unsigned int elementSize = 0; // Create an integer, store the size of each uniform (element) in the uniform buffer layout
			int currentElement = 0; // Create an integer, store the current element index in the 'SceneData' map, used to iterate through the uniform buffer elements and set their data

			UniformBufferLayout Layout = uboPair.first->getLayout(); // Create and set a uniform buffer layout class instance to the uniform buffer layout 

			for (auto uniformBufferElement : Layout) // For all of the uniform buffer elements in the uniform buffer layout, do the following
			{
				uboPair.first->setData(uniformBufferElement.m_offset, uniformBufferElement.m_size, uboPair.second[currentElement]); // Set the uniform buffer data, passing the current uniform variables (element) offset, size and data

				currentElement++; // Increment the counter, set data for the next uniform buffer element in the uniform buffer layout
			}
		}
	}

	void OpenGLBasicRenderer::submit(const std::shared_ptr<Material>& material) // Submit a material instance for drawing
	{
		auto Shader = material->getShader(); // Return and store the shader instance
		Shader->Bind(); // Bind the shader object to a rendering program instance

		auto Geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry()); // Return and store the vertex array object (geometry)
		Geometry->Bind(); // Bind the vertex array object

		auto perDrawData = material->getData(); // Return and store the uniform per draw data stored in the map

		for (auto dataPair : perDrawData) // For every pair (uniform name and its associated data) in the map, do the following
		{
			Shader->uploadData(dataPair.first, dataPair.second); // Upload the uniform variable data (create uniform variable for each type dispatched)
		}

		glDrawElements(GL_TRIANGLES, Geometry->getCount(), GL_UNSIGNED_INT, nullptr); // Draw the geometry (issue a draw call for the preceeding material)
	}
}