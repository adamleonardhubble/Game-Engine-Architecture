/** \file FPSCameraControllerEuler.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "FPSCameraControllerEuler.h" // Include FPSCameraControllerEuler.h file

#include "events/inputPoller.h" // Include inputPoller.h file

#include "events/event.h" // Include event.h file

namespace Engine // Engine namespace
{
	void FPSCameraControllerEuler::init(float fov, float aspectRatio, float nearClip, float farClip) // Initialise the properties of a perspective camera instance
	{
		m_camera.reset(new PerspectiveCamera3D(fov, aspectRatio, nearClip, farClip)); // Create an perspective camera instance, passing the intialiser values representing the camera perspective projection properties
		
		updateView(); // Update the camera view matrix function call (intialise view matrix)
	}

	void FPSCameraControllerEuler::onUpdate(float timestep) // Update camera controller properties, per passing frame
	{
		if (InputPoller::isKeyPressed(ENGINE_KEY_W)) { m_position += m_forward * m_translationSpeed * timestep; } // If the 'W' is pressed or held, translate the cameras position to move forwards (respectively)
		if (InputPoller::isKeyPressed(ENGINE_KEY_S)) { m_position -= m_forward * m_translationSpeed * timestep; } // If the 'S' is pressed or held, translate the cameras position to move backwards (respectively)
		if (InputPoller::isKeyPressed(ENGINE_KEY_A)) { m_position -= m_right * m_translationSpeed * timestep; } // If the 'A' is pressed or held, translate the cameras position to strafe left (respectively)
		if (InputPoller::isKeyPressed(ENGINE_KEY_D)) { m_position += m_right * m_translationSpeed * timestep; } // If the 'S' is pressed or held, translate the cameras position to strafe right (respectively)

		if (InputPoller::isMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT)) // If the 'left' mouse button is pressed (clicked) or held, do the following
		{
			glm::vec2 currentMousePosition = InputPoller::getMousePosition(); // Set 'currentMousePosition' to the current mouse position, upon holding
			glm::vec2 mouseDelta = currentMousePosition - m_lastMousePosition; // Set 'mouseDelta' to the current mouse position subtract the intial mouse position

			m_yaw -= mouseDelta.x * m_rotationSpeed * timestep; // Set the Euler angle 'Yaw', to subtract and equal the difference in mouse position within the 'X' axis 
			m_pitch -= mouseDelta.y * m_rotationSpeed * timestep; // Set the Euler angle 'Pitch', to subtract and equal the difference in mouse position within the 'Y' axis 

			if (m_pitch > 89.0f) // if 'm_pitch' is larger than '89.0' degrees, do the following
			{
				m_pitch = 89.0f; // Set 'm_pitch' to '89.0' degrees, constrain the angle looking upwards
			}
			if (m_pitch < -89.0f) // if 'm_pitch' is smaller than '-89.0' degrees, do the following
			{
				m_pitch = -89.0f; // Set 'm_pitch' to '-89.0' degrees, constrain the angle looking downwards
			}

			m_lastMousePosition = currentMousePosition; // Set 'm_lastMousePosition' to the current mouse position
		}

		updateView(); // Update the camera view matrix function call (update view matrix due to change)
	}

	void FPSCameraControllerEuler::updateView() // Update the camera view matrix
	{
		glm::vec3 forward; // A Vector3(floats), used to calculate the facing direction of the camera

		forward.x = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)); // Calculate the facing direction in the X axis, factoring the 'Yaw' and 'Pitch' Euler angles
		forward.y = sin(glm::radians(m_pitch)); // Calculate the facing direction in the Y axis, factoring the 'Pitch' Euler angle
		forward.z = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)); // Calculate the facing direction in the Z axis, factoring the 'Yaw' and 'Pitch' Euler angles

		m_forward = glm::normalize(forward); // Set 'm_forward' to the facing direction, normalised

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp)); // Set 'm_right' to the cross product of the facing direction and global upward axis, normalised
		m_up = glm::normalize(glm::cross(m_right, m_forward)); // Set 'm_up' to the cross product of the facing direction and local strafe axis, normalised

		m_view = glm::lookAt(m_position, m_position + m_forward, m_up); // Set 'm_view' to the passed position, target and up vectors (determines what the camera is looking at in the scene) 

		m_camera->setView(m_view); // Set the perspective cameras initial and updated view matrix
	}

	void FPSCameraControllerEuler::onEvent(Event & e) // Issue and dispatch camera controlled events
	{
		EventDispatcher dispatcher(e); // Create an 'EventDispatcher' class object, passing an event type

		dispatcher.dispatch<MouseButtonPressedEvent>(std::bind(&FPSCameraControllerEuler::onMouseButton, this, std::placeholders::_1)); // Dispatch mouse button pressed event, binds and returns mouse button pressed event, identifying handling state
	}

	void FPSCameraControllerEuler::onResize() // Update camera parameters to satisfy changing window size
	{

	}

	bool FPSCameraControllerEuler::onMouseButton(MouseButtonPressedEvent & e) // Get and set the previous mouse position
	{
		if (e.getMouseButton() == ENGINE_MOUSE_BUTTON_LEFT) // If the 'left' mouse button is pressed (clicked) or held, do the following
		{
			m_lastMousePosition = InputPoller::getMousePosition(); // Set 'm_lastMousePosition' to the current mouse position (when intially clicked)

			return true; // Return 'true' (mouse button pressed event occurred)
		}
		else // Else if the 'left' mouse button has not been pressed (clicked) or held, do the following
		{
			return false; // Return 'false' (mouse button pressed event has not occurred)
		}
	}
}
