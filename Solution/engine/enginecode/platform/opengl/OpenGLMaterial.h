/** \file OpenGLMaterial.h
*/

#pragma once // Compile once

#include "render/material.h" // Include material.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLMaterial
	\brief Class for OpenGL API specific materials. Provides means for
	* initialisation of OpenGL materials. Able to set and get shaders, 
	* vertex array objects for geometry being rendered and unifrom per draw
	* variable data which collectively compose a OpenGL API specific material.
	* Inherits from Material class.
	*/
	class OpenGLMaterial : public Material
	{
	private: // Private members
		std::shared_ptr<Shader> m_pShader; //!< Shared pointer, of type Shader class (pointer to Shader class)

		std::shared_ptr<VertexArray> m_pGeometry; //!< Shared pointer, of type VertexArray class (pointer to VertexArray class)

		std::map<std::string, void *> m_data; //!< Map, containing string and void pointer components (store uniform per draw data to be uploaded in renderer submit)

	public: // Public members
		//! Constructor, initialise the material instance
		/*!
		\param shader A reference to a pointer to the Shader class
		\param VAO A reference to a pointer to the VertexArray class
		*/
		OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);

		//! Set the shader used to compose a material instance
		/*!
		\param shader A reference to a pointer to the Shader class
		*/
		void setShader(const std::shared_ptr<Shader>& shader) override;

		//! Set the geometry used to compose a material instance
		/*!
		\param geometry A reference to the VertexArray 'or' VertexBuffer class, geometry data can be contained within a vertex array or vertex buffer object (renderer API specific)
		*/
		void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override;

		//! Set a block of data, as the uniform per draw variable data
		/*!
		\param data A reference to a map containing a pair of string and void pointer components
		*/
		void setDataBlock(const std::map<std::string, void *>& data) override;

		//! Set a single line of data, as a line of uniform variable data
		/*!
		\param dataName A reference to a string representing the name of the uniform variable data
		\param data A void pointer representing the data of the uniform variable
		*/
		void setDataElement(const std::string& dataName, void * data) override;

		//! Set vertex data directly
		/*!
		\param vertices A float type pointer representing the vertex data of the geometry to be set into the vertex buffer
		\param size A integer representing the size of the vertex data of the geometry
		\param offset A integer representing the offset between data lines in the vertex buffer layout
		*/
		//void setVertexData(float * vertices, unsigned int size, unsigned int offset) override;

		//! Return the shader used to compose a material instance
		/*!
		\return A pointer to the Shader class
		*/
		inline std::shared_ptr<Shader> getShader() override { return m_pShader; } 

		//! Return the geometry used to compose a material instance
		/*!
		\return A VertexArray 'or' VertexBuffer class pointer, geometry data can be contained within a vertex array or vertex buffer object (renderer API specific)
		*/
		inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() override { return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_pGeometry); }

		//! Return the uniform per draw variable data stored in the map, as the name of the uniform (string) and its associated data (void *)
		/*!
		\return A map of paired data representing the uniform per draw data stored in the map
		*/
		inline std::map<std::string, void *> getData() override { return m_data; }

	};
}