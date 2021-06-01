/** \file OpenGLMaterial.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "systems/log.h" // Include log.h file

#include "platform/opengl/OpenGLMaterial.h" // Include OpenGLMaterial.h file

namespace Engine // Engine namespace
{
	OpenGLMaterial::OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO) // Initialise the material instance
	{
		m_pShader = shader; // Set the passed shader class pointer to 'm_pShader'
		m_pGeometry = VAO; // Set the passed vertex array class pointer to 'm_pShader' 
	}

	void OpenGLMaterial::setShader(const std::shared_ptr<Shader>& shader) // Set the shader used to compose a material instance
	{
		m_pShader = shader; // Set the passed shader class pointer to 'm_pShader'
	}

	void OpenGLMaterial::setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) // Set the geometry used to compose a material instance
	{
		m_pGeometry = std::get<std::shared_ptr<VertexArray>>(geometry); // Set the passed vertex array class pointer to 'm_pGeometry' (OpenGL API specific)
	}

	void OpenGLMaterial::setDataBlock(const std::map<std::string, void *>& data) // Set a block of data, as the uniform per draw variable data
	{
		m_data.insert(data.begin(), data.end()); // Insert the passed data into the map of uniform per draw variable data
	}

	void OpenGLMaterial::setDataElement(const std::string& dataName, void * data) // Set a single line of data, as a line of uniform variable data
	{
		m_data.insert(std::make_pair(dataName, data)); // Insert the passed pair of data into the map of uniform per draw variable data
	}

	/*void OpenGLMaterial::setVertexData(float * vertices, unsigned int size, unsigned int offset)
	{
		
	}*/
}