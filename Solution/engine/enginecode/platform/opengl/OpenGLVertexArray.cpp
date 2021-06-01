/** \file OpenGLVertexArray.cpp
*/

#pragma once // Compile once

#include "engine_pch.h" // Include precompiled headers

#include "platform/opengl/OpenGLVertexArray.h" // Include OpenGLVertexArray.h file

#include <glad/glad.h> // Include glad.h file

namespace Engine // Engine namespace
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType dataType) // Convert shader data types to OpenGL type sizes
	{
		switch (dataType) // Switch case statement, controlled by the passed data type
		{
		case ShaderDataType::Int:		return GL_INT; // If the passed data type is of type 'int', return a 'GL int'
		case ShaderDataType::Int2:		return GL_INT; // If the passed data type is of type 'int2', return a 'GL int'
		case ShaderDataType::Int3:		return GL_INT; // If the passed data type is of type 'int3', return a 'GL int'
		case ShaderDataType::Int4:		return GL_INT; // If the passed data type is of type 'int4', return a 'GL int'
		case ShaderDataType::Float:		return GL_FLOAT; // If the passed data type is of type 'float', return a 'GL float'
		case ShaderDataType::Float2:	return GL_FLOAT; // If the passed data type is of type 'float2', return a 'GL float'
		case ShaderDataType::Float3:	return GL_FLOAT; // If the passed data type is of type 'float3', return a 'GL float'
		case ShaderDataType::Float4:	return GL_FLOAT; // If the passed data type is of type 'float4', return a 'GL float'
		case ShaderDataType::Mat3:		return GL_FLOAT; // If the passed data type is of type 'mat3', return a 'GL float'
		case ShaderDataType::Mat4:		return GL_FLOAT; // If the passed data type is of type 'mat4', return a 'GL float'
		case ShaderDataType::Bool:		return GL_BOOL; // If the passed data type is of type 'bool', return a 'GL bool'
		}

		return 0; // Return '0' (nothing)

	}

	OpenGLVertexArray::OpenGLVertexArray() // Create OpenGL vertex array
	{
		glCreateVertexArrays(1, &m_RendererID); // Create a new vertex array object, using the object ID (generate one (1) array object named m_RendererID)
	}

	OpenGLVertexArray::~OpenGLVertexArray() // Destructor
	{
		glDeleteVertexArrays(1, &m_RendererID); // Delete the vertex array object, using the object ID (delete one (1) array object named m_RendererID) 
	}
	
	void OpenGLVertexArray::Bind() const // Bind the vertex array object
	{
		glBindVertexArray(m_RendererID); // Bind the vertex array object
	}

	void OpenGLVertexArray::Unbind() const // Unbind the vertex array object
	{
		glBindVertexArray(0); // Unbind the vertex array object
	}

	void OpenGLVertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) // Set the vertex buffer
	{
		glBindVertexArray(m_RendererID); // Bind m_RendererID to the vertex array object
		vertexBuffer->Bind(); // Bind the vertex buffer object to the buffer data (vertex attributes)

		BufferLayout layout = vertexBuffer->getBufferLayout(); // Set BufferLayout class object 'layout' to the current vertex buffer object layout

		unsigned int m_vertexBufferIndex = 0; // Unsigned integer variable, used to store and cycle the index of the element (vertex attribute) being modified

		for (const auto& element : layout) // For all elements (vertex attributes) within the assigned vertex buffer layout, do the following
		{
			glEnableVertexAttribArray(m_vertexBufferIndex); // Enables a vertex attribute array, enabling each indexed element of the vertex attribute array (because it increments for every element in the buffer layout)

			// Specify the location and data format of an array of vertex attribute data, gathered from the vertex buffer layout, to be used when rendering to a window 
			glVertexAttribPointer(m_vertexBufferIndex, // The index of the vertex attribute, in the buffer layout, to be modified
				ShaderDataTypeComponentCount(element.m_dataType), // Get the elements data type size (bytes)
				ShaderDataTypeToOpenGLType(element.m_dataType), // Get the elements OpenGL data type conversion
				element.m_normalised ? GL_TRUE : GL_FALSE, // Determine whether the element is normalised or not normalised
				layout.getStride(), // Get the stride of the assigned vertex buffer layout (the offset (distance/ space) between consecutive lines of vertex attributes in the attribute array measured in bytes) - *the number of vertex data * its data type size (bytes), per line in the array*
				(const void*)element.m_offset); // Get the offset of the element - casted to a void pointer (the distance of the buffer layout element from the first buffer layout element in the attribute array for every line in the attribute array) - *the position of where the element starts in every line in the array*

			m_vertexBufferIndex++; // Incremenet vertex buffer index count (cycle to next element in the vertex buffer layout)
		}

		m_vertexBuffer = vertexBuffer; // Set the vertex buffer class pointer (local) to the bound vertex buffer class pointer passed - used for get vertex buffer
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) // Set the index buffer
	{
		glBindVertexArray(m_RendererID); // Bind m_RendererID to the vertex array object
		indexBuffer->Bind(); // Bind the index buffer object to the buffer data (vertex array indices)

		m_indexBuffer = indexBuffer; // Set the index buffer class pointer (local) to the bound index buffer class pointer passed - used for get index buffer
	}
}