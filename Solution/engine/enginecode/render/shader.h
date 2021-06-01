/** \file shader.h
*/

#pragma once // Compile once

#include <string> // Include string support

#include <map> // Include map support

#include "render/bufferLayout.h" // Include bufferLayout.h file

#include "render/uniformBufferLayout.h" // Include uniformBufferLayout.h file

#include "shaderDataTypes.h" // Include shaderDataTypes.h file

typedef std::pair<Engine::ShaderDataType, int> DataTypeAndLocation; //!< \typedef Pair containing a ShaderDataType enum and integer (uniform variable type and location)
using UniformLayout = std::map<std::string, DataTypeAndLocation>; //!< Uniform layout map, containing a string and a pair, used to store uniform variable information

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class Shader
	\brief Interface class for all render API shader programmes. Provides means for
	* initialisation and creation of shader programmes.
	*/
	class Shader
	{
	private: // Private members

	public: // Public members
		//! Return the API ID of the shader programme
		/*!
		\return A integer representing the shader programme API ID
		*/
		virtual unsigned int getID() = 0;

		virtual void Bind() const = 0; //! Bind the shader object
		virtual void Unbind() const = 0; //! Unbind the shader object

		//! Upload data of any type to the GPU
		/*!
		\param name A reference to a string representing the name asscoiated to the data
		\param data A void pointer representing the data to be uploaded
		\return A boolean representing whether data has been uploaded or not uploaded
		*/
		virtual bool uploadData(const std::string& name, void * data) = 0;

		//! Upload data of any type to the GPU
		/*!
		\param name A reference to the UniformLayout class (uniform variable layout)
		\return A boolean representing whether data has been uploaded or not uploaded
		*/
		virtual bool uploadData(const UniformLayout& uniforms) = 0;

		virtual BufferLayout getBufferLayout() const = 0; //!< Return the buffer layout for the shader

		virtual UniformLayout getUniformLayout() const = 0; //!< Return the structure of the uniform data that can be uploaded

		//! Return all instances of uniform buffer layouts
		/*!
		\return All instances of uniform buffer layout, stored within a map containing the name of the layout and the layout instance
		*/
		virtual std::map<std::string, UniformBufferLayout> getUniformBufferLayouts() = 0;

		//! Create, compile and link an API shader from a single filepath source
		/*!
		\param filepath A reference to a string representing the shaders memory location
		*/
		static Shader * Create(const std::string& filepath); //! Create a shader

		//! Create, compile and link an API shader from multiple filepath sources
		/*!
		\param vertexFilepath A reference to a string representing the vertex shader memory location
		\param fragmentFilepath A reference to a string representing the fragment shader memory location
		*/
		static Shader * Create(const std::string& vertexFilepath, const std::string& fragmentFilepath); //! Create a shader

	};
}