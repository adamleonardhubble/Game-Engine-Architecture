/** \file OpenGLUniformBuffer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "platform/opengl/OpenGLUniformBuffer.h" // Include OpenGLUniformBuffer.h file

#include <glad/glad.h> // Include glad.h file

namespace Engine // Engine namespace
{
	unsigned int OpenGLUniformBuffer::m_sBindingPoint = 0; // Initialise 'm_sBindingPoint', set to '0'

	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int size, UniformBufferLayout & layout) : m_Layout(layout) // Create a uniform buffer object instance
	{
		m_BindingPoint = m_sBindingPoint; // Set the uniform buffer object binding block to the current binding point globally 
		m_sBindingPoint++; // Increment the global binding point counter

		glGenBuffers(1, &m_UniformBufferID); // Create a ('1') uniform buffer object instance
		glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID); // Bind the uniform buffer object instance
		glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW); // Allocate memory and store the uniform buffer data in the intialised memory, within the currently bound uniform buffer object
		glBindBufferRange(GL_UNIFORM_BUFFER, m_BindingPoint, m_UniformBufferID, 0, size); // Bind the range of the uniform buffer object (between the starting offset and size), to the indexed binding point
	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout & layout) : m_Layout(layout) // Create a uniform buffer object instance
	{
		
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer() // Destructor
	{
		glDeleteBuffers(1, &m_UniformBufferID); // Delete the uniform buffer object, using the object ID (delete one (1) buffer object named m_UniformBufferID) 
	}

	void OpenGLUniformBuffer::bind() // Bind the uniform buffer object
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID); // Bind m_UniformBufferID to the uniform buffer data
	}

	void OpenGLUniformBuffer::unbind() // Unbind the uniform buffer object
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0); // Unbind m_UniformBufferID from the uniform buffer data
	}

	void OpenGLUniformBuffer::attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string & blockName) // Bind the shader block to a binding point
	{
		unsigned int uniformBlockIndex = glGetUniformBlockIndex(shader->getID(), blockName.c_str()); // Set 'uniformBlockIndex' to the shader programs uniform block index 

		glUniformBlockBinding(shader->getID(), uniformBlockIndex, m_BindingPoint); // Bind the shader programs uniform block to the corresponding binding point
	}

	void OpenGLUniformBuffer::setData(unsigned int offset, unsigned int size, void * data) // Set the uniform buffer data
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID); // Bind m_UniformBufferID to the uniform buffer data
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data); // Set the data of the currently bound uniform buffer object, within the specified range (between starting offset and size)
	}
}