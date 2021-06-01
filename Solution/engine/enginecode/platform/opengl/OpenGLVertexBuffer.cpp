/** \file OpenGLVertexBuffer.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "platform/opengl/OpenGLVertexBuffer.h" // Include OpenGLVertexBuffer.h file

#include <glad/glad.h> // Include glad.h file

namespace Engine // Engine namespace
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float * vertices, unsigned int size, BufferLayout& bufferLayout) : m_Layout(bufferLayout) // Set OpenGL vertex buffer data
	{
		glCreateBuffers(1, &m_RendererID); // Create a new vertex buffer object, using the object ID (generate one (1) buffer object named m_RendererID)
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // Bind m_RendererID to the buffer data (vertex attributes)
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Set the vertex data of the currently bound vertex buffer object
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer() // Destructor
	{
		glDeleteBuffers(1, &m_RendererID); // Delete the vertex buffer object, using the object ID (delete one (1) buffer object named m_RendererID) 
	}
	
	void OpenGLVertexBuffer::Bind() const // Bind the buffer object to the vertex attributes 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // Bind m_RendererID to the buffer data (vertex attributes)
	}
	
	void OpenGLVertexBuffer::Unbind() const // Unbind the vertex attributes from the previously binded buffer object
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind m_RendererID from the buffer data (vertex attributes)
	}

	void OpenGLVertexBuffer::edit(float * vertices, unsigned int size, unsigned int offset) //------>
	{

	}
}