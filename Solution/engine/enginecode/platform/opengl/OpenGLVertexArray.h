/** \file OpenGLVertexArray.h
*/

#pragma once // Compile once

#include "render/vertexArray.h" // Include vertexArray.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLVertexArray
	\brief Class for OpenGL API specific vertex arrays. Provides means for 
	* initialisation of OpenGL vertex arrays. Able to bind and unbind vertex
	* arrays. Able to set and retrieve vertex and index buffers.
	* Inherits from VertexArray class.
	*/
	class OpenGLVertexArray : public VertexArray
	{
	private: // Private members
		unsigned int m_RendererID; //!< Unsigned integer, store the renderer ID

		std::shared_ptr<VertexBuffer> m_vertexBuffer; //!< Shared pointer, of type VertexBuffer class (pointer to VertexBuffer class)
		
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< Shared pointer, of type IndexBuffer class (pointer to IndexBuffer class)

	public: // Public members
		//! Default constructor
		OpenGLVertexArray();

		//! Destructor
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override; //! Bind the vertex array object
		virtual void Unbind() const override; //! Unbind the vertex array object

		//! Return a vertex array indice count
		/*!
		\return A vertex array indice count (index buffer vertice count)
		*/
		virtual unsigned int getCount() const override { return m_indexBuffer->getCount(); }

		//! Set the vertex buffer 
		/*!
		\param vertexBuffer A reference to a VertexBuffer class pointer
		*/
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; //!< Override function,
		
		//! Set the index buffer 
		/*!
		\param indexBuffer A reference to a IndexBuffer class pointer
		*/
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override; //!< Override function,

		//! Return the vertex buffers 
		/*!
		\return A a pointer reference to the VertexBuffer class
		*/
		virtual const std::shared_ptr<VertexBuffer>& getVertexBuffers() const { return m_vertexBuffer; }
		
		//! Return the index buffer 
		/*!
		\return A a pointer reference to the IndexBuffer class
		*/
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return m_indexBuffer; }
	};
}