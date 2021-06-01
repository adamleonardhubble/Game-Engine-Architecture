/** \file bufferLayout.cpp
*/

#pragma once // Compile once

#include "engine_pch.h" // Include precompiled headers

#include "render/bufferLayout.h" // Include bufferLayout.h file

namespace Engine // Engine namespace
{
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements) // Calculate the stride and offsets of passed buffer layout elements
	{
		calculateStrideAndOffsets(); // Calculate the stride and offsets of buffer layout elements
	}
	
	void BufferLayout::calculateStrideAndOffsets() // Calculate the stride and offsets of buffer layout elements
	{
		unsigned int offset = 0; // Unsigned integer, store the offset of a vertex buffer layout
		
		m_stride = 0; // Unsigned integer, store the stride of a vertex buffer layout 

		for (auto& element : m_elements) // For all vertex buffer layout elements, do the following
		{
			element.m_offset = offset; // Set the currently indexed element offset, to the offset variable
			offset += element.m_size; // Add and equal the offset variable to the size of the element (bytes)
			m_stride += element.m_size; // Add and equal the stride variable to the size of the element (bytes)
		}
	}

	void BufferLayout::addElement(ShaderDataType dataType) // Add an element to a vertex buffer layout
	{
		m_elements.push_back(BufferElement(dataType)); // Push the elements onto the back of the initializer list

		calculateStrideAndOffsets(); // Calculate the stride and offsets of the added buffer layout elements
	}
}