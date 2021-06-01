/** \file OpenGLTexture.h
*/

#pragma once // Compile once

#include "render/texture.h" // Include texture.h file

#include "systems/log.h" // Include log.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OpenGLTexture
	\brief Class for OpenGL API specific textures. Provides means for
	* initialisation and creation of OpenGL textures. Inherits from 
	* Texture class.
	*/
	class OpenGLTexture : public Texture
	{
	private: // Private members
		unsigned int m_OpenGL_ID; //!< Unsigned integer, store the texture ID

		unsigned int m_textureWidth; //!< Unsigned integer, store the OpenGL texture width dimension
		unsigned int m_textureHeight; //!< Unsigned integer, store the OpenGL texture height dimension

		unsigned int m_textureChannels; //!< Unsigned integer, store the number of OpenGL texture channels

		unsigned int m_textureSlot; //!< Unsigned integer, store the GPU memory slot of the OpenGL texture

		static unsigned int s_textureSlot; //!< Unsigned integer, increment the amount of GPU memory slots storing OpenGL textures

	public: // Public members
		//! Constructor, set OpenGL texture data from file
		/*!
		\param filepath A reference to a string representing the textures memory location
		*/
		OpenGLTexture(const std::string& filepath);

		//! Constructor, set OpenGL texture data from raw data
		/*!
		\param width A integer representing the texture width dimension
		\param height A integer representing the texture height dimension
		\param channels A integer representing the number of texture channels
		\param texData A character pointer representing the texture data
		*/
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);

		//! Destructor
		virtual ~OpenGLTexture();

		//! Return the width of a texture
		/*!
		\return A integer representing the texture width dimension
		*/
		virtual unsigned int getWidth() const override { return m_textureWidth; }

		//! Return the height of a texture
		/*!
		\return A integer representing the texture height dimension
		*/
		virtual unsigned int getHeight() const override { return m_textureHeight; }

		//! Return the number of channels of a texture
		/*!
		\return A integer representing the number of texture channels (1 Greyscale, 3 RGB, 4 RGBA)
		*/
		virtual unsigned int getChannels() const override { return m_textureChannels; }

		//! Return the GPU memory slot where a texture is stored
		/*!
		\return A integer representing the textures memory slot in the GPU
		*/
		virtual unsigned int getSlot() const override { return m_textureSlot; }

	};
}