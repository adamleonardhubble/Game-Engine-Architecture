/** \file material.h
*/

#pragma once // Compile once

#include <string> // Include string support

#include <map> // Include map support

#include <memory> // Include memory support

#include <variant> // Include variant support

#include "render/shader.h" // Include shader.h file

#include "render/vertexArray.h" // Include vertexArray.h file

#include "render/vertexBuffer.h" // Include vertexBuffer.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class Material
	\brief Interface class for all render API materials. Provides means for
	* initialisation and creation of materials. Able to set and get shaders, 
	* vertices and indices of geometry being rendered and unifrom per draw
	* variable data which collectively compose a material.
	*/
	class Material
	{
	public: // Public members
		//! Create a material instance
		/*!
		\param shader A reference to a pointer to the Shader class
		\param VAO A reference to a pointer to the VertexArray class
		*/
		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);

		//! Create a material instance
		/*!
		\param shader A reference to a pointer to the Shader class
		\param VBO A reference to a pointer to the VertexBuffer class
		*/
		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO);

		//! Set the shader used to compose a material instance
		/*!
		\param shader A reference to a pointer to the Shader class
		*/
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0;

		//! Set the geometry used to compose a material instance
		/*!
		\param geometry A reference to the VertexArray 'or' VertexBuffer class, geometry data can be contained within a vertex array or vertex buffer object (renderer API specific)
		*/
		virtual void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0;

		//! Set a block of data, as the uniform per draw variable data
		/*!
		\param data A reference to a map containing a pair of string and void pointer components
		*/
		virtual void setDataBlock(const std::map<std::string, void *>& data) = 0;

		//! Set a single line of data, as a line of uniform variable data
		/*!
		\param dataName A reference to a string representing the name of the uniform variable data
		\param data A void pointer representing the data of the uniform variable
		*/
		virtual void setDataElement(const std::string& dataName, void * data) = 0;

		//! Set vertex data directly
		/*!
		\param vertices A float type pointer representing the vertex data of the geometry to be set into the vertex buffer
		\param size A integer representing the size of the vertex data of the geometry
		\param offset A integer representing the offset between data lines in the vertex buffer layout
		*/
		//virtual void setVertexData(float * vertices, unsigned int size, unsigned int offset) = 0;

		//! Return the shader used to compose a material instance
		/*!
		\return A pointer to the Shader class
		*/
		virtual std::shared_ptr<Shader> getShader() = 0;

		//! Return the geometry used to compose a material instance
		/*!
		\return A VertexArray 'or' VertexBuffer class pointer, geometry data can be contained within a vertex array or vertex buffer object (renderer API specific)
		*/
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() = 0;

		//! Return the uniform per draw variable data stored in the map, as the name of the uniform (string) and its associated data (void *)
		/*!
		\return A map of paired data representing the uniform per draw data stored in the map
		*/
		virtual std::map<std::string, void *> getData() = 0;

	};
}
