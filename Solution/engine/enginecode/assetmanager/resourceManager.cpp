/** \file resourceManager.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "assetmanager/resourceManager.h" // Include resourceManager.h file

namespace Engine // Engine namespace
{
	AssetManager<IndexBuffer> ResourceManager::m_indexBuffers; // Intialise 'm_indexBuffers', a 'IndexBuffer' class map instance within the 'AssetManager' template class
	AssetManager<VertexArray> ResourceManager::m_VAOs; // Intialise 'm_VAOs', a 'VertexArray' class map instance within the 'AssetManager' template class
	AssetManager<VertexBuffer> ResourceManager::m_VBOs; // Intialise 'm_VBOs', a 'VertexBuffer' class map instance within the 'AssetManager' template class
	AssetManager<UniformBuffer> ResourceManager::m_UBOs; // Intialise 'm_UBOs', a 'UniformBuffer' class map instance within the 'AssetManager' template class
	AssetManager<Shader> ResourceManager::m_shaders; // Intialise 'm_shaders', a 'Shader' class map instance within the 'AssetManager' template class
	AssetManager<Texture> ResourceManager::m_textures; // Intialise 'm_textures', a 'Texture' class map instance within the 'AssetManager' template class
	AssetManager<Material> ResourceManager::m_materials; // Intialise 'm_materials', a 'Material' class map instance within the 'AssetManager' template class

	std::shared_ptr<IndexBuffer> ResourceManager::addIndexBuffer(const std::string & name, unsigned int * indices, unsigned int count) // Create and add a index buffer object instance to the asset manager map
	{
		std::shared_ptr<IndexBuffer> temporaryPointer; // Create a temporary pointer
		temporaryPointer.reset(IndexBuffer::Create(indices, count)); // Create an index buffer object instance, passing indices and count of indices

		m_indexBuffers.add(name, temporaryPointer); // Add the index buffer object instance to the asset manager map, as a index buffer class pointer, passing the name

		return temporaryPointer; // Return 'temporaryPointer' (index buffer object instance)
	}

	std::shared_ptr<VertexArray> ResourceManager::addVAO(const std::string & name) // Create and add a vertex array object instance to the asset manager map
	{
		std::shared_ptr<VertexArray> temporaryPointer; // Create a temporary pointer
		temporaryPointer.reset(VertexArray::Create()); // Create a vertex array object

		m_VAOs.add(name, temporaryPointer); // Add the vertex array object instance to the asset manager map, as a vertex array class pointer, passing the name

		return temporaryPointer; // Return 'temporaryPointer' (vertex array object instance)
	}

	std::shared_ptr<VertexBuffer> ResourceManager::addVBO(const std::string & name, float * vertices, unsigned int size, BufferLayout & bufferLayout) // Create and add a vertex buffer object instance to the asset manager map
	{
		std::shared_ptr<VertexBuffer> temporaryPointer; // Create a temporary pointer
		temporaryPointer.reset(VertexBuffer::Create(vertices, size, bufferLayout)); // Create a vertex buffer object instance, passing vertices, size of vertices and a vertex buffer layout

		m_VBOs.add(name, temporaryPointer); // Add the vertex buffer object instance to the asset manager map, as a vertex buffer class pointer, passing the name

		return temporaryPointer; // Return 'temporaryPointer' (vertex buffer object instance)
	}

	std::shared_ptr<UniformBuffer> ResourceManager::addUBO(const std::string & name, unsigned int size, UniformBufferLayout & uniformBufferLayout, const std::string & shaderName) // Create a uniform buffer object instance, passing the UBO name, size of uniform data, UBO layout and name of shader object instance
	{
		std::shared_ptr<UniformBuffer> temporaryPointer; // Create a temporary pointer

		if (m_UBOs.contains(name)) // If the map of uniform buffer objects contains a uniform buffer object instance that corresponds to the passed name, do the following
		{
			temporaryPointer = m_UBOs.get(name); // Set the temporary pointer to the found uniform buffer object
		}
		else // If the map of uniform buffer objects does not contain a uniform buffer object instance that corresponds to the passed name, do the following
		{
			temporaryPointer.reset(UniformBuffer::Create(size, uniformBufferLayout)); // Create a uniform buffer object instance

			m_UBOs.add(name, temporaryPointer); // Add the created uniform buffer object instance, to the map of uniform buffer objects (passing the name)
		}
		
		temporaryPointer->attachShaderBlock(m_shaders.get(shaderName), name); // Bind the shader uniform block to a binding point, passing the shader object instance and shader uniform block name

		return temporaryPointer; // Return 'temporaryPointer' (uniform buffer object instance)
	}

	std::shared_ptr<Material> ResourceManager::addMaterial(const std::string& name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO) // Create and add a material object instance to the asset manager map
	{
		std::shared_ptr<Material> temporaryPointer; // Create a temporary pointer
		temporaryPointer.reset(Material::create(shader, VAO)); // Create a material object instance, passing a shader object instance pointer and vertex array object instance pointer

		m_materials.add(name, temporaryPointer); // Add the material object instance to the asset manager map, as a material class pointer, passing the name

		return temporaryPointer; // Return 'temporaryPointer' (material object instance)
	}

	std::shared_ptr<Shader> ResourceManager::addShader(const std::string & filepath) // Create and add a shader object instance to the asset manager map
	{
		std::shared_ptr<Shader> temporaryPointer; // Create a temporary pointer
		temporaryPointer.reset(Shader::Create(filepath)); // Create a shader object instance passing its filepath in memory

		m_shaders.add(parseFileSource(filepath), temporaryPointer); // Add the shader object instance to the asset manager map, as a shader class pointer, passing the filepath stripped from its paths and extensions (file name)

		std::map<std::string, UniformBufferLayout> uniformLayout = temporaryPointer->getUniformBufferLayouts(); // Create and set a map to all instances of shader uniform buffer layouts

		for (auto& uniformElement : uniformLayout) // For all uniform buffer elements within the uniform buffer layout map, do the following
		{
			addUBO(uniformElement.first, uniformElement.second.getElementSize(), uniformElement.second, parseFileSource(filepath)); // Create a UBO instance, passing the name of the shader block, uniform data size, the UBO layout and name of the shader source code file
		}

		return temporaryPointer; // Return 'temporaryPointer' (shader object instance)
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & filepath) // Create and add a texture object instance to the asset manager map
	{
		std::shared_ptr<Texture> temporaryPointer; // Create a temporary pointer
		temporaryPointer.reset(Texture::createFromFile(filepath)); // Create a texture object instance passing its filepath in memory

		m_textures.add(parseFileSource(filepath), temporaryPointer); // Add the texture object instance to the asset manager map, as a texture class pointer, passing the filepath stripped from its paths and extensions (file name)

		return temporaryPointer; // Return 'temporaryPointer' (texture object instance)
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & name, unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData) // Create and add a texture object instance to the asset manager map
	{
		std::shared_ptr<Texture> temporaryPointer; // Create a temporary pointer
		temporaryPointer.reset(Texture::createFromRawData(width, height, channels, texData)); // Create a texture object instance, passing width, height, number of channels and the texture data

		m_textures.add(name, temporaryPointer); // Add the texture object instance to the asset manager map, as a texture class pointer, passing the name

		return temporaryPointer; // Return 'temporaryPointer' (texture object instance)
	}

	std::string ResourceManager::parseFileSource(const std::string & sourceCodeFilepath) // Remove source code filepath directories and extension
	{
		std::string filepath = sourceCodeFilepath; // Set 'filepath' to the passed string (source code filepath)

		unsigned int positionToEraseUpTo = filepath.find_last_of('/'); // Set and create 'positionToEraseUpTo' to the position of the last '/' character (last path in the filepath)

		filepath.erase(0, positionToEraseUpTo + 1); // Erase characters from 'filepath', from the starting position to the position that the '/' character is 

		filepath.erase((filepath.find_last_of('.')), std::string::npos); // Erase characters from 'filepath', from the last '.' character to the end position of the string (remove file extension)

		return filepath; // Return the name of the file in the filepath passed
	}

	void ResourceManager::stop(SystemSignal close, ...) // Stop the resource management system (free all resources)
	{
		m_indexBuffers.emptyContainer(); // Empty index buffer object map
		m_VAOs.emptyContainer(); // Empty vertex array object map
		m_VBOs.emptyContainer(); // Empty vertex buffer object map
		m_UBOs.emptyContainer(); // Empty uniform buffer object map
		m_shaders.emptyContainer(); // Empty shader object map
		m_textures.emptyContainer(); // Empty texture object map
		m_materials.emptyContainer(); // Empty material object map
	}
}