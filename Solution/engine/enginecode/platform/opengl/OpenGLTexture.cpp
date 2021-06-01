/** \file OpenGLTexture.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "platform/opengl/OpenGLTexture.h" // Include OpenGLTexture.h file

#include "stb_image.h" // Include stb_image.h file

#include "core/core.h" // Include core.h file

#include <glad/glad.h> // Include glad.h file

namespace Engine // Engine namespace
{
	unsigned int OpenGLTexture::s_textureSlot = 0; // Set 's_textureSlot' to '0', there are no textures in the GPU memory slots

	OpenGLTexture::OpenGLTexture(const std::string& filepath) // Set OpenGL texture from a filepath
	{
		glGenTextures(1, &m_OpenGL_ID); // Generate a new texture object, using the object ID (generate one (1) texture object named m_OpenGL_ID)

		m_textureSlot = s_textureSlot; // Set the 'm_textureSlots' to the number of textures stored in GPU memory slots
		s_textureSlot++; // Increment the number of textures stored in GPU memory slots (new texture created)

		glActiveTexture(GL_TEXTURE0 + m_textureSlot); // Assign new texture object to the next slot in the GPU
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID); // Bind m_OpenGL_ID to the texture data

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Set the wrap of the texture coordinate 'S' to clamp to the edge of its primitives
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Set the wrap of the texture coordinate 'T' to clamp to the edge of its primitives

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Set the texture minification to linear mode, takes weighted average of the textures attributes closest to the texture coordinates (the coordinates of where the texture is clamped - edges)
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Set the texture magnification to linear mode, takes weighted average of the textures attributes closest to the texture coordinates (the coordinates of where the texture is clamped - edges)
		
		int textureWidth; // Integer variable, store the textures width dimension
		int textureHeight; // Integer variable, store the textures height dimension
		int textureChannels; // Integer variable, store the number of channels the textures has

		unsigned char * textureData = stbi_load(filepath.c_str(), &textureWidth, &textureHeight, &textureChannels, 0); // Load an image from a file (string), extrapolate its attributes (width, height, channels) and assign it to a character pointer (data of the texture)
		ENGINE_ASSERT(textureData, "failed to load texture image..."); // Assert if texture image could not be loaded into the string

		m_textureWidth = textureWidth; // Set 'm_textureWidth' to the textures width dimension
		m_textureHeight = textureHeight; // Set 'm_textureHeight' to the textures height dimension
		m_textureChannels = textureChannels; // Set 'm_textureChannels' to the textures number of channels

		if (textureData) // If the texture loads successfully, do the following
		{
			if (m_textureChannels == 3) // If the OpenGL texture has three channels, do the following
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 3); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData); // Create a 2D texture image (RGB)
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
			}
			else if (m_textureChannels == 4) // Else if the OpenGL texture has four channels, do the following
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureWidth, m_textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData); // Create a 2D texture image (RGBA)
			}
			else if (m_textureChannels == 1) // Else if the OpenGL texture has one channel, do the following
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_textureWidth, m_textureHeight, 0, GL_RED, GL_UNSIGNED_BYTE, textureData); // Create a 2D texture image (red)
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
			}
			else return; // Else return

			glGenerateMipmap(GL_TEXTURE_2D); // Generate and allocate a mipmaps memory for a 2D texture object
		}
		else // If the texture does not load, do the following
		{
			return; // Return
		}

		stbi_image_free(textureData); // Free the loaded texture image stored on the CPU
	}

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData) : m_textureWidth(width),
		m_textureHeight(height), m_textureChannels(channels) // Set OpenGL texture from raw data
	{
		glGenTextures(1, &m_OpenGL_ID); // Generate a new texture object, using the object ID (generate one (1) texture object named m_OpenGL_ID)

		m_textureSlot = s_textureSlot; // Set the 'm_textureSlots' to the number of textures stored in GPU memory slots
		s_textureSlot++; // Increment the number of textures stored in GPU memory slots (new texture created)

		glActiveTexture(GL_TEXTURE0 + m_textureSlot); // Assign new texture object to the next slot in the GPU
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID); // Bind m_OpenGL_ID to the texture data

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Set the wrap of the texture coordinate 'S' to clamp to the edge of its primitives
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Set the wrap of the texture coordinate 'T' to clamp to the edge of its primitives

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Set the texture minification to linear mode, takes weighted average of the textures attributes closest to the texture coordinates (the coordinates of where the texture is clamped - edges)
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Set the texture magnification to linear mode, takes weighted average of the textures attributes closest to the texture coordinates (the coordinates of where the texture is clamped - edges)
		
		if (channels == 3) // If the OpenGL texture has three channels, do the following
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData); // Create a 2D texture image (RGB)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
		}
		else if (channels == 4) // Else if the OpenGL texture has four channels, do the following
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData); // Create a 2D texture image (RGBA)
		}
		else if (channels == 1) // Else if the OpenGL texture has one channel, do the following
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texData); // Create a 2D texture image (red)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Set the pixel store mode of the texture, set the allignment requirements for the start of each pixel row in memory
		}
		else return; // Else return

		glGenerateMipmap(GL_TEXTURE_2D); // Generate and allocate a mipmaps memory for a 2D texture object
	}

	OpenGLTexture::~OpenGLTexture() // Destructor
	{
		glDeleteTextures(1, &m_OpenGL_ID); // Delete the texture object, using the object ID (delete one (1) texture object named m_OpenGL_ID) 
	}
}
