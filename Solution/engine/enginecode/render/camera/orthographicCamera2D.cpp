/** \file orthographicCamera2D.cpp
*/

#include "engine_pch.h" // Include percompiled headers

#include <glm/gtc/matrix_transform.hpp> // Include glm matrix transformation support

#include "render/camera/orthographicCamera2D.h" // Include orthographicCamera2D.h file

namespace Engine // Engine namespace
{
	OrthographicCamera2D::OrthographicCamera2D(float left, float right, float bottom, float top) // Set the camera view frustum properties 
	{
		reset(left, right, bottom, top); // Reset the camera view frustum properties, passing the values of each view frustum border
	}

	void OrthographicCamera2D::reset(float left, float right, float bottom, float top) // Reset the camera view frustum properties
	{
		m_projection = glm::ortho(left, right, bottom, top); // Set 'm_projection' to the orthographic projection, passing the view frustum initialiser values
		m_view = glm::mat4(1.0f); // Set 'm_view' to a matrix that is central in relation to the orthographic projection

		m_viewProjection = m_projection * m_view; // Calculate the view projection matrix
	}

	void OrthographicCamera2D::updateView() // Update the camera view matrix
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_position, 1.0f)); // Set 'translate' to be the translation component of the camera view matrix, that varies based upon the value of 'm_position' (all axis)
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Set 'rotate' to be the rotation component of the camera view matrix, that varies based upon the value of 'm_rotation' (angle)
		
		m_view = translate * rotate; // Calculate the view matrix (translation and rotation matrices multipled)

		m_viewProjection = m_projection * m_view; // Calculate the view projection matrix (view and projection matrices multiplied)
	}
}
