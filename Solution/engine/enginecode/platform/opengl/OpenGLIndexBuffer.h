/** \file OpenGLIndexBuffer.h
*/

#pragma once // Compile once

#include "render/indexBuffer.h" // Include indexBuffer.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLIndexBuffer
	\brief Class for OpenGL API specific index buffers. Provides means for 
	* initialisation of OpenGL index buffers. Able to bind and unbind index 
	* buffer objects to index attributes. Able to retrieve vertex array indice 
	* count. Inherits from IndexBuffer class.
	*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	private: // Private members
		unsigned int m_Count; //!< Unsigned integer, store the buffer count
		unsigned int m_RendererID; //!< Unsigned integer, store the renderer ID

	public: // Public members
		//! Constructor, set a OpenGL index buffer data
		/*!
		\param indices A integer type pointer representing the index data to be set into the buffer
		\param count A integer representing the size of the index data to be set into the buffer
		\return A index buffer with set data
		*/
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		
		//! Destructor
		virtual ~OpenGLIndexBuffer(); 

		virtual void Bind() const override; //! Bind the buffer object to the index attributes 
		virtual void Unbind() const override; //! Unbind the index attributes from the previously binded buffer object

		//! Return a vertex array indice count
		/*!
		\return A vertex array indice count
		*/
		virtual unsigned int getCount() const override { return m_Count; }

	};
}
