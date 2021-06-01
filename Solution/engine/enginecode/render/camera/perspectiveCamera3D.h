/** \file perspectiveCamera3D.h
*/

#pragma once // Compile once

#include <glm/glm.hpp> // Include glm support

#include <glm/gtx/quaternion.hpp> // Include glm quaternion support

#include "render/camera/camera.h" // Include camera.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class PerspectiveCamera3D
	\brief Class for perspective specific cameras. Provides means for
	* initialisation of perspective camera properties. Able to reset the
	* properties of a perspective camera instance, set and get the view, 
	* position and orientation of a perspective camera instance. Inherits 
	* from the Camera class.
	*/
	class PerspectiveCamera3D : public Camera
	{
	private: // Private members
		glm::vec3 m_position = glm::vec3(0.0f); //!< Float, representing the position of the camera

		glm::quat m_orientation; //!< Float, representing the orientation of the camera (quaternion camera only)

		void updateView() override {}; //!< Update the camera view matrix (not used)

	public: // Public members
		//! Constructor, set the camera perspective projection properties
		/*!
		\param fov A float representing the field of view angle
		\param aspectRatio A float representing the aspect ratio of the camera viewport
		\param nearClip A float representing the relative distance to the cameras near clipping plane
		\param farClip A float representing the relative distance to the cameras far clipping plane
		*/
		PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip);

		//! Reset the camera perspective projection properties
		/*!
		\param fov A float representing the field of view angle
		\param aspectRatio A float representing the aspect ratio of the camera viewport
		\param nearClip A float representing the relative distance to the cameras near clipping plane
		\param farClip A float representing the relative distance to the cameras far clipping plane
		*/
		void reset(float fov, float aspectRatio, float nearClip, float farClip);

		//! Return the position of the camera
		/*!
		\return A Vector3(floats) representing the position of the camera instance
		*/
		inline glm::vec3 getPosition() { return m_position; }

		//! Return the orientation of the camera (quaternion camera only)
		/*!
		\return A quaternion representing the orientation of the camera instance
		*/
		inline glm::quat getOrientation() { return m_orientation; }

		//! Set the view matrix of the camera and calculate the view projection matrix (Euler camera only)
		/*!
		\param view A matrix representing the view (position) of the camera
		*/
		void setView(const glm::mat4& view) { m_view = view; m_viewProjection = m_projection * m_view; }

		//! Set and update the position of the camera (quaternion camera only)
		/*!
		\param position A Vector3(floats) reference representing the position of the camera instance
		*/
		void setPosition(const glm::vec3& position) { m_position = position; updateView(); }

		//! Set the orientation of the camera (quaternion camera only)
		/*!
		\param orientation A quaternion representing the the orientation of the camera (all axis)
		*/
		void setOrientation(const glm::quat& orientation) { m_orientation = orientation; updateView(); }

		//! Set the position and orientation of the camera (quaternion camera only)
		/*!
		\param position A Vector3(floats) representing the position of the camera instance
		\param orientation A quaternion representing the orientation of the camera instance
		*/
		void setPositionAndOrientation(const glm::vec3& position, const glm::quat& orientation) { m_position = position; m_orientation = orientation; updateView(); }

	};
}
