/** \file resourceManager.h
*/

#pragma once // Compile once

#include "include/independent/systems/system.h" // Include system.h file

#include "render/indexBuffer.h" // Include indexBuffer.h file

#include "render/vertexBuffer.h" // Include vertexBuffer.h file

#include "render/uniformBuffer.h" // Include uniformBuffer.h file

#include "render/vertexArray.h" // Include vertexArray.h file

#include "render/texture.h" // Include texture.h file

#include "render/shader.h" // Include shader.h file

#include "render/material.h" // Include material.h file

#include "assetmanager/assetManager.h" // Include assetManager.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class ResourceManager
	\brief Class for managing application resources. Provides means for the
	* creation, addition and identification of class pointers to the asset 
	* manager map. Makes use of asset manager template class to create and add 
	* new class object instances which are stored as shared pointer types.
	* Inherits from System class.
	*/
	class ResourceManager : public System
	{
	private: // Private members
		static AssetManager<IndexBuffer> m_indexBuffers; //!< A 'IndexBuffer' class map instance within the 'AssetManager' template class
		static AssetManager<VertexArray> m_VAOs; //!< A 'VertexArray' class map instance within the 'AssetManager' template class
		static AssetManager<VertexBuffer> m_VBOs; //!< A 'VertexBuffer' class map instance within the 'AssetManager' template class
		static AssetManager<UniformBuffer> m_UBOs; //!< A 'UniformBuffer' class map instance within the 'AssetManager' template class
		static AssetManager<Shader> m_shaders; //!< A 'Shader' class map instance within the 'AssetManager' template class
		static AssetManager<Texture> m_textures; //!< A 'Texture' class map instance within the 'AssetManager' template class
		static AssetManager<Material> m_materials; //!< A 'Material' class map instance within the 'AssetManager' template class

		//! Remove source code filepath directories and extension
		/*!
		\param src A reference to a string representing the filepath of the source code being parsed
		*/
		static std::string parseFileSource(const std::string& sourceCodeFilepath);
		
		//////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////// Text label code ////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////
		static const int m_ASCIIstart = 32;
		static const int m_ASCIIend = 126;
		//static std::map<std::string, std::vector<Character>> m_characters; ///!< Renderable characters
		static std::shared_ptr<Texture> m_fontTexture; ///!< Texture to store fonts
		//////////////////////////////////////////////////////////////////////////////////////////////

	public: // Public members
		//!< Default constructor
		ResourceManager() {};

		void start(SystemSignal init = SystemSignal::None, ...) {}; //!< Start the resource management system
		void stop(SystemSignal close, ...); //!< Stop the resource management system (free all resources)

		//! Create and add a index buffer object instance to the asset manager map
		/*!
		\param name A reference to a string representing the name of the index buffer object instance
		\param indices A integer representing the index data to be set into the buffer
		\count A integer representing the size of the index data to be set into the buffer
		\return A pointer representing the index buffer object data
		*/
		static std::shared_ptr<IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);

		//! Create and add a vertex array object instance to the asset manager map
		/*!
		\param name A reference to a string representing the name of the vertex array object instance
		\return A pointer representing the vertex array object data
		*/
		static std::shared_ptr<VertexArray> addVAO(const std::string& name);

		//! Create and add a vertex buffer object instance to the asset manager map
		/*!
		\param name A reference to a string representing the name of the vertex buffer object instance
		\param vertices A float type pointer representing the vertex data to be set into the buffer
		\param size A integer representing the size of the vertex data to be set into the buffer
		\param bufferLayout A reference to the BufferLayout class (layout of vertex buffer)
		\return A pointer representing the vertex buffer object data
		*/
		static std::shared_ptr<VertexBuffer> addVBO(const std::string& name, float* vertices, unsigned int size, BufferLayout& bufferLayout);

		//! Create and add a uniform buffer object instance to the asset manager map
		/*!
		\param name A reference to a string representing the name of the uniform buffer object instance
		\param size A integer representing the size of the uniform data to be set into the buffer
		\param uniformBufferLayout A reference to the UniformBufferLayout class (layout of uniform buffer)
		\param shaderName A reference to a string representing the name of the shader object instance
		*/
		static std::shared_ptr<UniformBuffer> addUBO(const std::string& name, unsigned int size, UniformBufferLayout& uniformBufferLayout, const std::string& shaderName);

		//! Return a uniform buffer object pointer by passing its name
		/*!
		\param name A reference to a string representing the name of the uniform buffer object pointer
		\return A pointer appointed to a uniform buffer object
		*/
		static std::shared_ptr<UniformBuffer> getUBO(const std::string& name) { return m_UBOs.get(name); }
		
		//! Create and add a shader object instance to the asset manager map
		/*!
		\param filepath A reference to a string representing the shaders memory location 
		\return A pointer representing the shader object data
		*/
		static std::shared_ptr<Shader> addShader(const std::string& filepath);

		//! Create and add a texture object instance to the asset manager map
		/*!
		\param filepath A reference to a string representing the textures memory location
		\return A pointer representing the texture object data
		*/
		static std::shared_ptr<Texture> addTexture(const std::string& filepath);

		//! Create and add a texture object instance to the asset manager map
		/*!
		\param name A reference to a string representing the name of the texture object instance
		\param width A integer representing the texture width dimension
		\param height A integer representing the texture height dimension
		\param channels A integer representing the number of texture channels
		\param texData A character pointer representing the texture data
		\return A pointer representing the texture object data
		*/
		static std::shared_ptr<Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);

		//! Create and add a material object instance to the asset manager map
		/*!
		\param name A reference to a string representing the name of the material object instance
		\param shader A pointer appointed to the Shader class, a shader object instance
		\param VAO A pointer appointed to the VertexArray class, a vertex array object instance
		*/
		static std::shared_ptr<Material> addMaterial(const std::string& name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////// Text label code /////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//static void populateCharacters(std::unordered_map<std::string, unsigned int> fontsAndSizes);

		//static std::shared_ptr<Character> getCharacter(std::string font, unsigned int ASCIIcide);

		//inline static std::shared_ptr<Texture> getFontTexture() { return m_fontTexture; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	};
}