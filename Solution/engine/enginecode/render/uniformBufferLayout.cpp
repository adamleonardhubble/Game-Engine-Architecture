/** \file uniformBufferLayout.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "render/uniformBufferLayout.h" // Include uniformBufferLayout.h file

namespace Engine // Engine namespace
{
	UniformBufferLayout::UniformBufferLayout(const std::initializer_list<UniformBufferElement>& elements) : m_elements(elements) // Calculate the stride and offsets of passed uniform buffer layout elements
	{
		calculateStrideAndOffsets(); // Calculate the stride and offsets of uniform buffer layout elements
	}

	void UniformBufferLayout::calculateStrideAndOffsets() // Calculate the stride and offsets of uniform buffer layout elements
	{
		unsigned int offset = 0; // Unsigned integer, store the offset of a uniform buffer layout

		m_stride = 0; // Unsigned integer, store the stride of a uniform buffer layout 

		m_size = 0;

		for (auto& element : m_elements) // For all uniform buffer layout elements, do the following
		{
			element.m_offset = offset; // Set the currently indexed element offset, to the offset variable
			
			int Remainder = element.m_size % 16; // Create and set a integer variable, to the remainder of the uniform element size relative to being a multiple of '16'
			
			if (Remainder == 0) // If the remainder is equal to '0' (a multiple of '16', there is no remainder), do the following
			{
				offset += element.m_size; // Set the offset to the element size (element size is '16' bytes (mat4))
			}
			else // If there is a remainder, do the following
			{
				offset += ((element.m_size + 16) - Remainder); // Set the offset to the element size plus '16' (allignment size) minus the remainder, to make a '16' byte allignment (offset)
			}

			m_size += element.m_size;

			m_stride += element.m_size; // Add and equal the stride variable to the size of the element (bytes)
		}
	}

	void UniformBufferLayout::addElement(ShaderDataType dataType) // Add an element to a uniform buffer layout
	{
		m_elements.push_back(UniformBufferElement(dataType)); // Push the elements onto the back of the initializer list

		calculateStrideAndOffsets(); // Calculate the stride and offsets of the added buffer layout elements
	}
}