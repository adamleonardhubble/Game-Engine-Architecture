/** \file freeOrthoCameraController2D.h
*/

#pragma once // Compile once

#include <glm/glm.hpp> // Include glm support

#include "render/camera/cameraController.h" // Include cameraController.h file

#include "render/camera/orthographicCamera2D.h" // Include orthographicCamera2D.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class FreeOrthoCameraController2D
	\brief Class for orthographic specific camera controllers. Provides means for
	* initialisation of orthographic camera properties. Able to return a orthographic 
	* camera instance, update orthographic camera controller properties, dispatch orthographic 
	* camera controlled events and update orthographic camera properties when the window is 
	* resized. Inherits from the CameraController class.
	*/
	class FreeOrthoCameraController2D : public CameraController
	{
	private: // Private members
		std::shared_ptr<OrthographicCamera2D> m_camera; //!< Shared pointer, of type OrthographicCamera2D class (pointer to OrthographicCamera2D class)
		
		glm::vec2 m_position = glm::vec3(0.0f); //!< A float, representing the position of the camera

		float m_rotation = 0.0f; //!< A float, representing the rotation of the camera

		float m_translationSpeed = 100.0f; //!< A float, representing the translation speed of the cameras change in position

		float m_rotationSpeed = 10.0f; //!< A float, representing the rotation speed of the cameras change in angle

	public: // Public members
		//! Default constructor
		FreeOrthoCameraController2D() {};

		//! Initialise the properties of a orthographic camera instance
		/*!
		\param left A float representing the left border of the camera view frustum
		\param top A float representing the top border of the camera view frustum
		\param width A float representing the right border of the camera view frustum
		\param height A float representing the bottom border of the camera view frustum
		*/
		void init(float left, float top, float width, float height) override;

		//! Return a shared pointer appointed to a camera class
		/*!
		\return A shared pointer appointed to a camera class
		*/
		std::shared_ptr<Camera> getCamera() override { return m_camera; }

		//! Update orthographic camera controller properties, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		void onUpdate(float timestep) override;

		//! Issue and dispatch orthographic camera controlled events
		/*!
		\param e A reference to the Event class
		*/
		void onEvent(Event& e) override;

		void onResize() override; //!< Update orthographic camera parameters to satisfy changing window size

	};
}
