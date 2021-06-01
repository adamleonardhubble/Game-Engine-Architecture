/** \file OpenGLVertexBuffer.h
*/

#pragma once // Compile once

#include "render/vertexBuffer.h" // Include indexBuffer.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLVertexBuffer
	\brief Class for OpenGL specific vertex buffers. Provides means for 
	* initialisation of OpenGL vertex buffers. Able to bind and unbind vertex buffer 
	* objects to vertex attributes. Able to retrieve vertex buffer layout also. 
	* Inherits from VertexBuffer class.
	*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private: // Private members
		unsigned int m_RendererID; //!< Unsigned integer, store the renderer ID (vertex object)

		BufferLayout m_Layout; //!< BufferLayout class object

	public: // Public members
		//! Constructor, set OpenGL vertex buffer data
		/*!
		\param vertices A float type pointer representing the vertex data to be set into the buffer
		\param size A integer representing the size of the vertex data to be set into the buffer
		\param bufferLayout A reference to the BufferLayout class (layout of vertex buffer)
		*/
		OpenGLVertexBuffer(float * vertices, unsigned int size, BufferLayout& bufferLayout);

		//! Destructor
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override; //! Bind the buffer object to the vertex attributes 
		virtual void Unbind() const override; //! Unbind the vertex attributes from the previously binded buffer object

		virtual void edit(float * vertices, unsigned int size, unsigned int offset) override; //----->

		//! Return a vertex buffer layout
		/*!
		\return A vertex buffer layout
		*/
		virtual const BufferLayout& getBufferLayout() const override { return m_Layout; }

	};
}