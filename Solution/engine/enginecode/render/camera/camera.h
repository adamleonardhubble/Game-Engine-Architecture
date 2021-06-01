/** \file camera.h
*/

#pragma once // Compile once

#include <glm/glm.hpp> // Include glm support

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class Camera
	\brief Base class for all cameras. Provides means for
	* initialisation of camera components. Able to return the projection matrix,
	* return the view matrix, return the view projection matrix of cameras and
	* update the camera view matrix.
	*/
	class Camera
	{
	protected: // Protected members
		glm::mat4 m_projection; //!< A matrix, set the projection (frustum) matrix of a camera

		glm::mat4 m_view; //!< A matrix, set the view (position) matrix of a camera

		glm::mat4 m_viewProjection; //!< A matrix, set the view projection (position and frustum) matrix of a camera

	public: // Public members
		virtual void updateView() = 0; //!< Update the camera view matrix

		//! Return the projection matrix
		/*!
		\return A matrix representing the projection (frustum) of a camera (4x4)
		*/
		const glm::mat4& getProjection() { return m_projection; }

		//! Return the view matrix
		/*!
		\return A matrix representing the view (position) of a camera (4x4)
		*/
		const glm::mat4& getView() { return m_view; }

		// Return the view projection matrix
		/*!
		\return A matrix representing the view and projection matrices (position and frustum) of a camera (4x4)
		*/
		const glm::mat4& getViewProjection() { return m_viewProjection; }

	};
}