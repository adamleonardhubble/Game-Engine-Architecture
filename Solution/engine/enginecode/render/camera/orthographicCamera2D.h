/** \file orthographicCamera2D.h
*/

#pragma once // Compile once

#include <glm/glm.hpp> // Include glm support

#include "render/camera/camera.h" // Include camera.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class OrthographicCamera2D
	\brief Class for orthographic specific cameras. Provides means for
	* initialisation of orthographic camera properties. Able to reset the
	* properties of a orthographic camera instance, update the view matrix of
	* a orthographic camera and set and get the position and rotation of a 
	* orthographic camera instance. Inherits from the Camera class.
	*/
	class OrthographicCamera2D : public Camera
	{
	private: // Private members
		glm::vec2 m_position = glm::vec2(0.0f); //!< Float, representing the position of the camera

		float m_rotation = 0.0f; //!< Float, representing the rotation of the camera

		void updateView() override; //!< Update the camera view matrix

	public: // Public members
		//! Constructor, set the camera view frustum properties 
		/*!
		\param left A float representing the left border of the camera view frustum
		\param right A float representing the right border of the camera view frustum
		\param bottom A float representing the bottom border of the camera view frustum
		\param top A float representing the top border of the camera view frustum
		*/
		OrthographicCamera2D(float left, float right, float bottom, float top);

		//! Reset the camera view frustum properties
		/*!
		\param left A float representing the left border of the camera view frustum
		\param right A float representing the right border of the camera view frustum
		\param bottom A float representing the bottom border of the camera view frustum
		\param top A float representing the top border of the camera view frustum
		*/
		void reset(float left, float right, float bottom, float top);

		//! Return the position of the camera
		/*!
		\return A Vector2(floats) representing the position of the camera instance 
		*/
		inline glm::vec2 getPosition() const { return m_position; }

		//! Return the rotation of the camera
		/*!
		\return A float representing the rotation of the camera instance
		*/
		inline float getRotation() const { return m_rotation; }

		//! Set and update the position of the camera
		/*!
		\param position A Vector2(floats) reference representing the position of the camera instance
		*/
		void setPosition(const glm::vec2& position) { m_position = position; updateView(); }

		//! Set and update the rotation of the camera
		/*!
		\param rotation A float representing the rotation of the camera instance
		*/
		void setRotation(float rotation) { m_rotation = rotation; updateView(); }

		//! Set and update the position and rotation of the camera
		/*!
		\param position A Vector2(floats) reference representing the position of the camera instance
		\param rotation A float representing the rotation of the camera instance
		*/
		void setPositionRotation(const glm::vec2& position, float rotation) { m_position = position; m_rotation = rotation; updateView(); }

	};
}