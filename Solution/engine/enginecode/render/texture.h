/** \file texture.h
*/

#pragma once // Compile once

#include <string> // Include string support

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class Texture
	\brief Interface class for all render API textures. Provides means for
	* initialisation and creation of textures.
	*/
	class Texture 
	{
	private: // Private members

	public: // Public members
		//! Return the width of a texture
		/*!
		\return A integer representing the texture width dimension
		*/
		virtual unsigned int getWidth() const = 0;

		//! Return the height of a texture
		/*!
		\return A integer representing the texture height dimension
		*/
		virtual unsigned int getHeight() const = 0;

		//! Return the number of channels of a texture
		/*!
		\return A integer representing the number of texture channels (1 Greyscale, 3 RGB, 4 RGBA)
		*/
		virtual unsigned int getChannels() const = 0;

		//! Return the GPU memory slot where a texture is stored
		/*!
		\return A integer representing the textures memory slot in the GPU
		*/
		virtual unsigned int getSlot() const = 0;

		//! Create a texture from a filepath
		/*!
		\param filepath A reference to a string representing the textures memory location
		*/
		static Texture * createFromFile(const std::string& filepath);

		//! Create a texture from raw data
		/*!
		\param width A integer representing the texture width dimension
		\param height A integer representing the texture height dimension
		\param channels A integer representing the number of texture channels
		\param texData A character pointer representing the texture data
		*/
		static Texture * createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);

	};
}
