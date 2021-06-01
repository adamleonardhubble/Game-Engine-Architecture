/** \file vertexBuffer.h
*/

#pragma once // Compile once

#include "render/bufferLayout.h" // Include bufferLayout.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class VertexBuffer
	\brief Interface class for all render API vertex buffers. Provides means for 
	* initialisation of vertex buffers. Able to bind and unbind vertex buffer objects 
	* to vertex attributes. Able to retrieve vertex buffer layout also.
	*/
	class VertexBuffer
	{
	public: // Public members
		//! Default destructor
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0; //! Bind the buffer object to the vertex attributes 
		virtual void Unbind() const = 0; //! Unbind the vertex attributes from the previously binded buffer object

		virtual void edit(float* vertices, unsigned int size, unsigned int offset) = 0; //----> 

		//! Return a vertex buffer layout
		/*!
		\return A vertex buffer layout
		*/
		virtual const BufferLayout& getBufferLayout() const = 0;

		//! Create a renderer vertex buffer
		/*!
		\param vertices A float type pointer representing the vertex data to be set into the buffer
		\param size A integer representing the size of the vertex data to be set into the buffer
		\param bufferLayout A reference to the BufferLayout class (layout of vertex buffer)
		\return A vertex buffer with set data
		*/
		static VertexBuffer* Create(float* vertices, unsigned int size, BufferLayout& bufferLayout); //!< Return a rendering API specific vertex buffer
	};
}
