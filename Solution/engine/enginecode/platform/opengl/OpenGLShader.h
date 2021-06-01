/** \file OpenGLShader.h
*/

#pragma once // Compile once

#include "render/shader.h" // Include shader.h file

#include "systems/log.h" // Include log.h file

#include <glad/glad.h> // Include glad.h file

#include "render/uniformBufferLayout.h" // Include uniformBufferLayout.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLShader
	\brief Class for OpenGL API specific shader programmes. Provides means for
	* initialisation and creation of OpenGL shader programmes. Inherits from
	* Shader class.
	*/
	class OpenGLShader : public Shader
	{
	private: // Private members
		unsigned int m_OpenGL_ID; //!< Unsigned integer, store the shader programme ID

		unsigned int m_vertexShader; //!< Unsigned integer, vertex shader object
		unsigned int m_fragmentShader; //!< Unsigned integer, fragment shader object

		const char * m_singleSource; //!< Character pointer, store the vertex and fragment shader source code (single source)

		const char * m_vertexSource; //!< Character pointer, store the vertex shader source code
		const char * m_fragmentSource; //!< Character pointer, store the fragment shader source code

		BufferLayout m_ShaderLayout; //!< BufferLayout class object

		UniformLayout m_UniformLayout; //!< UniformLayout map object

		bool bFoundShaderUniformBlock = false; //!< Boolean, determine whether a shader uniform block (layout (std140) uniform Matrices etc) has been found

		std::map<std::string, UniformBufferLayout> m_uniformBufferLayout; //!< Uniform layout map, containing a string and a 'UniformBufferLayout' class instance, used to store uniform variable information

		std::string ShaderBlockName; //!< String, store the name of a found shader uniform block

	public: // Public members
		//! Constructor, create, compile and link shader from a single filepath source
		/*!
		\param filepath A reference to a string representing the shaders memory location
		*/
		OpenGLShader(const std::string& filepath);

		//! Constructor, create, compile and link shader from multiple filepath sources
		/*!
		\param vertexFilepath A reference to a string representing the vertex shader memory location
		\param fragmentFilepath A reference to a string representing the fragment shader memory location
		*/
		OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);

		//! Destructor
		virtual ~OpenGLShader();

		//! Return the API ID of the shader programme
		/*!
		\return A integer representing the shader programme API ID
		*/
		virtual unsigned int getID() override { return m_OpenGL_ID; }

		virtual void Bind() const override; //! Bind the shader object
		virtual void Unbind() const override; //! Unbind the shader object

		//! Upload data of any type to the GPU
		/*!
		\param name A reference to a string representing the name asscoiated to the data
		\param data A void pointer representing the data to be uploaded
		\return A boolean representing whether data has been uploaded or not uploaded
		*/
		virtual bool uploadData(const std::string& name, void * data) override;

		//! Upload data of any type to the GPU
		/*!
		\param name A reference to the UniformLayout class (uniform variable layout)
		\return A boolean representing whether data has been uploaded or not uploaded
		*/
		virtual bool uploadData(const UniformLayout& uniforms) override;

		//! Dispatch shader uniform variable data
		/*!
		\param dataType A enumerator type representing a shader data type 
		\param uniformLocation A integer representing the uniform variable location
		\param uniformData A void pointer representing the uniform variable data
		*/
		void dispatchUniformData(ShaderDataType dataType, GLuint uniformLocation, void * uniformData);

		//! Extract the uniform layout (per-line)
		/*!
		\param line A reference to a string representing the vertex and fragment uniform layout source code memory location
		\param uniformBlock A boolean representing whether the line being extracted is a shader uniform block
		*/
		void extractUniformLayout(const std::string& line, bool uniformBlock);

		//! Return all instances of uniform buffer layouts
		/*!
		\return All instances of uniform buffer layout, stored within a map containing the name of the layout and the layout instance
		*/
		virtual std::map<std::string, UniformBufferLayout> getUniformBufferLayouts() override { return m_uniformBufferLayout; }

		//! Extract the buffer layout (per-line)
		/*!
		\param line A reference to a string representing the vertex buffer layout source code memory location 
		*/
		void extractBufferLayout(const std::string& line);

		virtual BufferLayout getBufferLayout() const override { return m_ShaderLayout; } //!< Return the buffer layout for the shader

		virtual UniformLayout getUniformLayout() const override { return m_UniformLayout; } //!< Return the structure of the uniform data that can be uploaded

		//! Resolve shader source code into its components, compile and link shader components
		/*!
		\param filepath A reference to a string representing the shader souce code memory location
		*/
		void parseSource(const std::string & filepath); 

		//! Resolve shader source code into its components, compile and link shader components
		/*!
		\param vertexFilepath A reference to a string representing the vertex shader souce code memory location
		\param fragmentFilepath A reference to a string representing the fragment shader souce code memory location
		*/
		void parseSource(const std::string& vertexFilepath, const std::string& fragmentFilepath);

		//! Compile and link shader programme
		/*!
		\param vertexShader A string representing the vertex shader region of the source code
		\param fragmentShader A string representing the fragment shader region of the source code
		*/
		void compileAndLink(const std::string vertexShader, const std::string fragmentShader);

	};
}