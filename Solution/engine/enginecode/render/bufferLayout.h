/** \file bufferLayout.h
*/

#pragma once // Compile once

#include "render/shaderDataTypes.h" // Include shaderDataTypes.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class BufferElement
	\brief Class for vertex buffer elements. Provides means for initialisation of vertex 
	* buffer element data.
	*/
	class BufferElement
	{
	public: // Public members
		ShaderDataType m_dataType; //!< Enum class object, access memory data types
		unsigned int m_size; //!< Unsigned integer, store the size of the data type passed
		unsigned int m_offset; //!< Unsigned integer, store the offset of a buffer layout element
		bool m_normalised; //!< Boolean variable, determine whether a shader data type variable is normalised or not normalised

		//! Default constructor
		BufferElement() {}; 

		//! Constructor, set the buffer element data
		/*!
		\param dataType A enumerator type representing a shader data type 
		\param normalised A boolean representing whether a shader data type variable is normalised or not normalised
		*/
		BufferElement(ShaderDataType dataType, bool normalised = false)
			: m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalised(normalised) {};
	};

	/**
	\class BufferLayout
	\brief Class for vertex buffer layouts. Provides means for initialisation of vertex 
	* buffer layouts. Able to calculate vertex buffer layout stride and offsets. Able to 
	* iterate through vertex buffer layout elements. Able to add an element to a vertex 
	* buffer layout.
	*/
	class BufferLayout
	{
	private: // Private members
		std::vector<BufferElement> m_elements; //!< Vector of buffer element class elements

		unsigned int m_stride; //!< Unsigned integer, the size in bytes used to store the offset (distance/ space) between consecutive lines of vertex attributes in the attribute array - the number of vertex data * its data type size (bytes), per line in the array

		void calculateStrideAndOffsets(); //!< Function, calculates the stride distance and the offset for each vertex buffer element

	public: // Public members
		//! Default constructor
		BufferLayout() {};

		//! Constructor, intialise buffer element class members
		/*!
		\param elements A reference to the buffer element class (to initialise class members)
		*/
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		//! Return the stride of a vertex buffer layout
		/*!
		\return A integer representing the stride distance between vertex buffer layout attribute lines
		*/
		inline unsigned int getStride() const { return m_stride; }

		//! Return the beggining vertex buffer layout element
		/*!
		\return A vector of buffer element class elements (first element)
		*/
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }

		//! Return the ending vertex buffer layout element
		/*!
		\return A vector of buffer element class elements (last element)
		*/
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }

		//! Return the beggining vertex buffer layout element
		/*!
		\return A vector of buffer element class elements (first element)
		*/
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }

		//! Return the ending vertex buffer layout element
		/*!
		\return A vector of buffer element class elements (last element)
		*/
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

		//! Add a element to a vertex buffer layout
		/*!
		\param dataType A enumerator type representing the shader data type of an element
		*/
		void addElement(ShaderDataType dataType);
	};
}

