/** \file vertexArray.h
*/

#pragma once // Compile once

#include "render/vertexBuffer.h" // Include vertexBuffer.h file

#include "render/indexBuffer.h" // Include indexBuffer.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class VertexArray
	\brief Interface class for all render API vertex arrays. Provides means for 
	* initialisation of vertex arrays. Able to bind and unbind vertex arrays. 
	* Able to set and retrieve vertex and index buffers.
	*/
	class VertexArray
	{
	public: // Public members
		//! Default destructor
		virtual ~VertexArray() {};

		static VertexArray* Create(); //! Create a renderer vertex array

		virtual void Bind() const = 0; //! Bind the vertex array object
		virtual void Unbind() const = 0; //! Unbind the vertex array object

		//! Return a vertex array indice count
		/*!
		\return A vertex array indice count
		*/
		virtual unsigned int getCount() const = 0;

		//! Set the vertex buffer 
		/*!
		\param vertexBuffer A reference to a VertexBuffer class pointer
		*/
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

		//! Set the index buffer 
		/*!
		\param indexBuffer A reference to a IndexBuffer class pointer
		*/
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		//! Return the vertex buffers 
		/*!
		\return A a pointer reference to the VertexBuffer class
		*/
		virtual const std::shared_ptr<VertexBuffer>& getVertexBuffers() const = 0;

		//! Return the index buffer 
		/*!
		\return A a pointer reference to the IndexBuffer class
		*/
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
	};
}
