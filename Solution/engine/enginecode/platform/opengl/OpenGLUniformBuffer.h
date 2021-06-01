/** \file OpenGLUniformBuffer.h
*/

#pragma once // Compile once

#include "render/uniformBuffer.h" // Include uniformBuffer.h file

#include "render/uniformBufferLayout.h" // Include uniformBuffer.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLUniformBuffer
	\brief Class for OpenGL specific uniform buffers. Provides means for
	* initialisation of OpenGL uniform buffers. Able to bind and unbind uniform buffer objects,
	* bind shader uniform blocks to binding points. Able to retrieve uniform buffer 
	* object layouts also. Inherits from UniformBuffer class.
	*/
	class OpenGLUniformBuffer : public UniformBuffer
	{
	private: // Private members
		unsigned int m_UniformBufferID; //!< Unsigned integer, store the uniform buffer ID

		UniformBufferLayout m_Layout; //!< UniformBufferLayout class object

		unsigned int m_BindingPoint; //!< Unsigned integer, store the shader data block binding point

		static unsigned int m_sBindingPoint; //!< Unsigned integer, store the shader data block binding point

	public: // Public members
		//! Constructor, create a uniform buffer object instance
		/*!
		\param size A integer representing the size of the uniform buffer object instance
		\param layout A reference to the UniformBufferLayout class (layout of uniform buffer)
		*/
		OpenGLUniformBuffer(unsigned int size, UniformBufferLayout& layout);

		//! Constructor, create a uniform buffer object instance
		/*!
		\param size A integer representing the size of the uniform buffer object instance
		\param rangeStart A integer representing the starting range of uniform data blocks a uniform buffer object is bound by
		\param rangeEnd A integer representing the ending range of uniform data blocks a uniform buffer object is bound by
		\param layout A reference to the UniformBufferLayout class (layout of uniform buffer)
		*/
		OpenGLUniformBuffer(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout);

		//!< Destructor
		~OpenGLUniformBuffer();

		virtual void bind() override; //! Bind the uniform buffer object

		virtual void unbind() override; //! Unbind the uniform buffer object

		//! Bind the shader uniform block to a binding point
		/*!
		\param shader A reference to a pointer to the Shader class
		\param blockName A reference to a string representing the name of the uniform data block
		*/
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) override;

		//! Set the uniform buffer data
		/*!
		\param offset A integer representing the offset between lines of data in the uniform buffer
		\param size A integer representing the size of the uniform data to be set into the buffer
		\param data A void pointer representing the data of the uniform being set into the buffer
		*/
		virtual void setData(unsigned int offset, unsigned int size, void * data) override;

		//! Return a uniform buffer layout
		/*!
		\return A buffer layout of a uniform buffer object
		*/
		inline UniformBufferLayout getLayout() const override { return m_Layout; }

	};
}
