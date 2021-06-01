/** \file indexBuffer.h
*/

#pragma once // Compile once

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class IndexBuffer
	\brief Interface class for all render API index buffers. Provides means for 
	* initialisation of index buffers. Able to bind and unbind index buffer objects 
	* to index attributes. Able to retrieve vertex array indice count.
	*/
	class IndexBuffer
	{
	public: // Public members
		//! Default deconstructor
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0; //! Bind the buffer object to the index attributes 
		virtual void Unbind() const = 0; //! Unbind the index attributes from the previously binded buffer object

		//! Return a vertex array indice count
		/*!
		\return A vertex array indice count
		*/
		virtual unsigned int getCount() const = 0;

		//! Create a renderer index buffer
		/*!
		\param indices A integer type pointer representing the index data to be set into the buffer
		\param count A integer representing the size of the index data to be set into the buffer
		\return A index buffer with set data
		*/
		static IndexBuffer* Create(unsigned int* indices, unsigned int count);
	};
}
