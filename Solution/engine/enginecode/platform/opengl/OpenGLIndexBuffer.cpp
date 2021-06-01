/** \file OpenGLIndexBuffer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "platform/opengl/OpenGLIndexBuffer.h" // Include OpenGLIndexBuffer.h file

#include <glad/glad.h> // Include glad.h file

namespace Engine // Engine namespace
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count) : m_Count(count) // Set OpenGL index buffer data
	{
		glCreateBuffers(1, &m_RendererID); // Create a new index buffer object, using the object ID (generate one (1) buffer object named m_RendererID)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // Bind m_RendererID to the buffer data (vertex array indices)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW); // Set the index data of the currently bound index buffer object
	}
	
	OpenGLIndexBuffer::~OpenGLIndexBuffer() // Destructor
	{
		glDeleteBuffers(1, &m_RendererID); // Delete the index buffer object, using the object ID (delete one (1) buffer object named m_RendererID) 
	}
	
	void OpenGLIndexBuffer::Bind() const // Bind the buffer object to the vertex array indices 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // Bind m_RendererID to the buffer data (vertex array indices)
	}
	
	void OpenGLIndexBuffer::Unbind() const // Unbind the vertex array indices from the previously binded buffer object
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind m_RendererID from the buffer data (vertex array indices)
	}
}