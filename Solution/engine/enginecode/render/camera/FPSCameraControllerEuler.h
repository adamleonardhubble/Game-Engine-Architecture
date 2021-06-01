/** \file FPSCameraControllerEuler.h
*/

#pragma once // Compile once

#include <glm/glm.hpp> // Include glm support

#include "render/camera/cameraController.h" // Include cameraController.h file

#include "render/camera/perspectiveCamera3D.h" // Include perspectiveCamera.h file

#include "events/mouseEvent.h" // Include mouseEvent.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class FPSCameraControllerEuler
	\brief Class for perspective specific camera controllers. Provides means for
	* initialisation of perspective camera properties. Able to return a perspective
	* camera instance, update perspective camera controller properties, dispatch perspective
	* camera controlled events, update perspective camera properties when the window is
	* resized and get and set the position of the mouse. Inherits from the CameraController class.
	*/
	class FPSCameraControllerEuler : public CameraController
	{
	private: // Private members
		std::shared_ptr<PerspectiveCamera3D> m_camera; //!< Shared pointer, of type PerspectiveCamera3D class (pointer to PerspectiveCamera3D class)

		glm::mat4 m_view; //!< A matrix, set the view (position) matrix of a camera

		glm::vec3 m_position = glm::vec3(0.0f, 0.0f, -4.5f); //!< A float, representing the position of the camera

		glm::vec3 m_forward = glm::vec3(0.0f); //!< A Vector3(floats), representing the axis of the camera that is used for a camera to translate towards or away from objects (Z axis equivalent) - relative to the cameras local orientation

		glm::vec3 m_up = glm::vec3(0.0f); //!< A Vector3(floats), representing the axis of the camera that is used for a camera to translate upwards or downwards (Y axis equivalent) - relative to the cameras local orientation

		glm::vec3 m_right = glm::vec3(0.0f); //!< A Vector3(floats), representing the axis of the camera that is used for a camera to strafe left or right (X axis equivalent) - relative to the cameras local orientation

		glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f); //!< A Vector3(floats), representing the axis of the camera that always remains upwards regardless of the cameras orientation (Y axis equivalent) - relative to the cameras global orientation

		float m_yaw = 0.0f; //!< A float, representing the Euler angle 'Yaw'

		float m_pitch = 0.0f; //!< A float, representing the Euler angle 'Pitch'

		float m_translationSpeed = 2.0f; //!< A float, representing the translation speed of the cameras change in position

		float m_rotationSpeed = 2.0f; //!< A float, representing the rotation speed of the cameras change in angle

		glm::vec2 m_lastMousePosition; //!< A Vector2(floats), representing the position of the mouse when intially pressed

		void updateView(); //!< Update the camera view matrix

	public: // Public members
		//! Default constructor
		FPSCameraControllerEuler() {};
		
		//! Initialise the properties of a perspective camera instance
		/*!
		\param fov A float representing the field of view angle
		\param aspectRatio A float representing the aspect ratio of the camera viewport
		\param nearClip A float representing the relative distance to the cameras near clipping plane
		\param farClip A float representing the relative distance to the cameras far clipping plane
		*/
		void init(float fov, float aspectAspect, float nearClip, float farClip) override;

		//! Return a shared pointer appointed to a camera class
		/*!
		\return A shared pointer appointed to a camera class
		*/
		std::shared_ptr<Camera> getCamera() override { return m_camera; }

		//! Update camera controller properties, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		void onUpdate(float timestep) override;

		//! Issue and dispatch camera controlled events
		/*!
		\param e A reference to the Event class
		*/
		void onEvent(Event& e) override;

		void onResize() override; //!< Update camera parameters to satisfy changing window size

		//! Get and set the previous mouse position
		/*!
		\param e A reference to the MouseButtonPressedEvent class
		\return A boolean representing whether a mouse button pressed event occured
		*/
		bool onMouseButton(MouseButtonPressedEvent& e);

	};
}