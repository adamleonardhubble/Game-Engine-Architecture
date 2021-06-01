/** \file freeOrthoCameraController2D.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "freeOrthoCameraController2D.h" // Include freeOrthoCameraController2D.h file

#include "events/inputPoller.h" // Include inputPoller.h file

#include "events/event.h" // Include event.h file

namespace Engine // Engine namespace
{
	void FreeOrthoCameraController2D::init(float left, float top, float width, float height) // Initialise the properties of a orthographic camera instance
	{
		m_camera.reset(new OrthographicCamera2D(left, left + width, top + height, top)); // Create an orthographic camera instance, passing the intialiser values representing the camera view frustum

		m_position = glm::vec2(left, top); // Set 'm_position' to the top-left corner of the camera view frustum

		m_camera->setPosition(m_position); // Set the orthographic cameras initial position
		m_camera->setRotation(m_rotation); // Set the orthographic cameras initial rotation
	}

	void FreeOrthoCameraController2D::onUpdate(float timestep) // Update orthographic camera controller properties, per passing frame
	{
		////////////////////////////////////////////
		//////// Position control of camera ////////
		////////////////////////////////////////////

		if (InputPoller::isKeyPressed(ENGINE_KEY_W)) // If the 'W' key is pressed or held, do the following
		{
			m_position.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move upwards relative to the rotation of the camera and translation speed (X axis)
			m_position.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move upwards relative to the rotation of the camera and translation speed (Y axis)
		}
		if (InputPoller::isKeyPressed(ENGINE_KEY_S)) // If the 'S' key is pressed or held, do the following
		{
			m_position.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move downwards relative to the rotation of the camera and translation speed (X axis)
			m_position.y += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move downwards relative to the rotation of the camera and translation speed (Y axis)
		}
		if (InputPoller::isKeyPressed(ENGINE_KEY_A)) // If the 'A' key is pressed or held, do the following
		{
			m_position.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move left relative to the rotation of the camera and translation speed (X axis)
			m_position.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move left relative to the rotation of the camera and translation speed (Y axis)
		}
		if (InputPoller::isKeyPressed(ENGINE_KEY_D)) // If the 'D' key is pressed or held, do the following
		{
			m_position.x += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move right relative to the rotation of the camera and translation speed (X axis)
			m_position.y += sin(glm::radians(m_rotation)) * m_translationSpeed * timestep; // Move right relative to the rotation of the camera and translation speed (X axis)
		}

		////////////////////////////////////////////
		//////// Rotation control of camera ////////
		////////////////////////////////////////////

		if (InputPoller::isKeyPressed(ENGINE_KEY_Q)) // If the 'Q' key is pressed or held, do the following
		{
			m_rotation -= timestep * m_rotationSpeed; // Set 'm_rotation' to continually substract itself from the camera rotation speed, relative to the time passed since the last frame was made (rotate left)

			if (m_rotation > 180.0f) // If the camera rotation is larger than '180' degrees, do the following
			{
				m_rotation -= 360.0f; // Substract '360' degrees from the camera rotation (-180 degrees)
			}
			else if (m_rotation <= -180.0f) // Else if the camera rotation is smaller than or equal to '-180' degress, do the following
			{
				m_rotation += 360.0f; // Add '360' degrees to the camera rotation (180 degrees)
			}
		}
		if (InputPoller::isKeyPressed(ENGINE_KEY_E)) // If the 'E' key is pressed or held, do the following
		{
			m_rotation += timestep * m_rotationSpeed; // Set 'm_rotation' to continually substract itself from the camera rotation speed, relative to the time passed since the last frame was made (rotate right)

			if (m_rotation > 180.0f) // If the camera rotation is larger '180' degrees, do the following
			{
				m_rotation -= 360.0f; // Subtract '360' degrees from the camera rotation (-180 degrees)
			}
			else if (m_rotation <= -180.0f) // Else if the camera rotation is smaller than or equal to '-180' degrees, do the following
			{
				m_rotation += 360.0f; // Add '360' degrees to the camera rotation (180 degrees)
			}
		}

		m_camera->setPositionRotation(m_position, m_rotation); // Set the orthographic cameras position and rotation (update)
	}

	void FreeOrthoCameraController2D::onEvent(Event & e) // Issue and dispatch orthographic camera controlled events
	{
		
	}

	void FreeOrthoCameraController2D::onResize() // Update orthographic camera parameters to satisfy changing window size
	{

	}

}