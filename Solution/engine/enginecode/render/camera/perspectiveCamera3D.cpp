/** \file perspectiveCamera3D.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "perspectiveCamera3D.h" // Include perspectiveCamera3D.h file

namespace Engine // Engine namespace
{
	PerspectiveCamera3D::PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip) // Set the camera perspective projection properties
	{
		reset(fov, aspectRatio, nearClip, farClip); // Reset the camera perspective projection properties, passing the values of the projections field of view, aspect ratio and clipping plane distances
	}

	void PerspectiveCamera3D::reset(float fov, float aspectRatio, float nearClip, float farClip) // Reset the camera perspective projection properties
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip); // Set 'm_projection' to the perspective projection, passing the projection initialiser values
		m_view = glm::mat4(1.0f); // Set 'm_view' to a matrix that is central in relation to the perspective projection

		m_viewProjection = m_projection * m_view; // Calculate the view projection matrix
	}
}
