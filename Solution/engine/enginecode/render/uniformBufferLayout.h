/** \file uniformBufferLayout.h
*/

#pragma once // Compile once

#include "render/shaderDataTypes.h" // Include shaderDataTypes.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class UniformBufferElement
	\brief Class for uniform buffer elements. Provides means for initialisation of uniform
	* buffer element data.
	*/
	class UniformBufferElement
	{
	public: // Public members
		ShaderDataType m_dataType; //!< Enum class object, access memory data types
		unsigned int m_size; //!< Unsigned integer, store the size of the data type passed
		unsigned int m_offset; //!< Unsigned integer, store the offset of a uniform buffer layout element
		bool m_normalised; //!< Boolean variable, determine whether a shader data type variable is normalised or not normalised

		//! Default constructor
		UniformBufferElement() {};

		//! Constructor, set the buffer element data
		/*!
		\param dataType A enumerator type representing a shader data type
		\param normalised A boolean representing whether a shader data type variable is normalised or not normalised
		*/
		UniformBufferElement(ShaderDataType dataType, bool normalised = false)
			: m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalised(normalised) {};
	};

	/**
	\class UniformBufferLayout
	\brief Class for uniform buffer layouts. Provides means for initialisation of uniform
	* buffer layouts. Able to calculate uniform buffer layout stride and offsets. Able to
	* iterate through uniform buffer layout elements. Able to add an element to a uniform
	* buffer layout.
	*/
	class UniformBufferLayout
	{
	private: // Private members
		std::vector<UniformBufferElement> m_elements; //!< Vector of uniform buffer element class elements

		unsigned int m_stride; //!< Unsigned integer, the size in bytes used to store the offset (distance/ space) between consecutive lines of uniform data (variables)

		unsigned int m_size;

		void calculateStrideAndOffsets(); //!< Function, calculates the stride distance and the offset for each uniform buffer element

	public: // Public members
		//! Default constructor
		UniformBufferLayout() {};

		//! Constructor, intialise uniform buffer element class members
		/*!
		\param elements A reference to the UniformBufferElement class (to initialise class members)
		*/
		UniformBufferLayout(const std::initializer_list<UniformBufferElement>& elements);

		//! Return the stride of a uniform buffer layout
		/*!
		\return A integer representing the stride distance between uniform buffer layout attribute lines
		*/
		inline unsigned int getStride() const { return m_stride; }

		inline unsigned int getElementSize() const { return m_size; }

		//! Return the beggining uniform buffer layout element
		/*!
		\return A vector of uniform buffer element class elements (first element)
		*/
		std::vector<UniformBufferElement>::iterator begin() { return m_elements.begin(); }

		//! Return the ending uniform buffer layout element
		/*!
		\return A vector of uniform buffer element class elements (last element)
		*/
		std::vector<UniformBufferElement>::iterator end() { return m_elements.end(); }

		//! Return the beggining uniform buffer layout element
		/*!
		\return A vector of uniform buffer element class elements (first element)
		*/
		std::vector<UniformBufferElement>::const_iterator begin() const { return m_elements.begin(); }

		//! Return the ending uniform buffer layout element
		/*!
		\return A vector of uniform buffer element class elements (last element)
		*/
		std::vector<UniformBufferElement>::const_iterator end() const { return m_elements.end(); }

		//! Add a element to a uniform buffer layout
		/*!
		\param dataType A enumerator type representing the shader data type of an element
		*/
		void addElement(ShaderDataType dataType);

	};
}