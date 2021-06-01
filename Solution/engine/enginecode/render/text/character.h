/** \file character.h
*/

#pragma once // Compile once

#include <glm/glm.hpp> // Include glm support

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class Character
	\brief Interface class for all text renderers. Provides means for
	* initialisation and creation of text renderers.
	*/
	class Character
	{
	private: // Private members
		glm::vec2 m_startUV; //!< Vector2(floats), representing the top-left UV coordinates of a character glyph

		glm::vec2 m_endUV; //!< Vector2(floats), representing the bottom-right UV coordinates of a character glyph

		glm::ivec2 m_size; //!< Vector2(integers), representing the size of a character glyph

		glm::ivec2 m_bearing; //!< Vector2(integers), representing the bearing of a character glyph (position relative to an origin)

		int m_advance; //!< Integer, store the distance from the next character

	public: // Public members
		//! Default constructor
		Character() {};

		//! Constructor, set character glpyh parameters
		/*!
		\param size A vector2(integers) representing the size of the character glyph
		\param bearing A vector2(integers) representing the bearing of the character glyph
		\param advance A integer representing the distance to the next character glyph, from the current one
		\param startUV A vector2(floats) representing the top-left UV coordinates of a character glyph
		\param endUV A vector2(floats) representing the bottom-right UV coordinates of a character glyph
		*/
		Character(glm::ivec2 size, glm::ivec2 bearing, int advance, glm::vec2 startUV = glm::vec2(0.0f, 0.0f), glm::vec2 endUV = glm::vec2(0.0f, 0.0f)) 
			: m_size(size), m_bearing(bearing), m_advance(advance), m_startUV(startUV), m_endUV(endUV) {};

		//! Set the starting and ending UV coordinates
		/*!
		\param startUV A vector2(floats) representing the starting UV coordinates
		\param endUV A vector2(floats) representing the ending UV coordinates
		*/
		void setUVs(glm::vec2 startUV, glm::vec2 endUV) { m_startUV = startUV; m_endUV = endUV; }

		//! Return the top-left UV coordinates of a character glyph
		/*!
		\return A vector2(floats) representing the starting UV coordinates
		*/
		inline glm::vec2 getStartUV() { return m_startUV; }

		//! Return the bottom-right UV coordinates of a character glyph
		/*!
		\return A vector2(floats) representing the ending UV coordinates
		*/
		inline glm::vec2 getEndUV() { return m_endUV; }

		//! Return the size of a character glyph
		/*!
		\return A vector2(integers) representing the size of a character glyph
		*/
		inline glm::ivec2 getSize() { return m_size; }

		//! Return the bearing of a character glyph
		/*!
		\return A vector2(integers) representing the bearing of a character glyph
		*/
		inline glm::ivec2 getBearing() { return m_bearing; }

		//! Return the distance from the next character glyph
		/*!
		\return A integer representing the distance from the next character
		*/
		inline int getAdvance() { return m_advance; } 
	};
}