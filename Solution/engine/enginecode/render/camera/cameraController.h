/** \file cameraController.h
*/

#pragma once // Compile once

#include <memory> // Include memory support

#include "render/camera/camera.h" // Include camera.h file

#include "events/event.h" // Include event.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class CameraController
	\brief Base class for all camera controllers. Provides means for
	* initialisation of camera properties. Able to return a camera instance,
	* update camera controller properties, dispatch camera controlled events
	* and update camera properties when the window is resized.
	*/
	class CameraController
	{
	public: // Public members
		//! Initialise the properties of a camera instance
		/*!
		\param float A float representing a property of a camera instance (dynamic use)
		\param float A float representing a property of a camera instance (dynamic use)
		\param float A float representing a property of a camera instance (dynamic use)
		\param float A float representing a property of a camera instance (dynamic use)
		*/
		virtual void init(float, float, float, float) = 0;

		//! Return a shared pointer appointed to a camera class
		/*!
		\return A shared pointer appointed to a camera class
		*/
		virtual std::shared_ptr<Camera> getCamera() = 0;

		//! Update camera controller properties, per passing frame
		/*!
		\param timestep A float representing the time passed since the last frame was made
		*/
		virtual void onUpdate(float timestep) = 0;

		//! Issue and dispatch camera controlled events
		/*!
		\param e A reference to the Event class
		*/
		virtual void onEvent(Event& e) = 0;

		virtual void onResize() = 0; //!< Update camera parameters to satisfy changing window size

	};
}