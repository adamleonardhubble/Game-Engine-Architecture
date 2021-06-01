/** \file GLFWWindowInputPoller.h
*/

#pragma once // Compile once

#include "core/application.h" // Include application.h file

#include "events/inputPoller.h" // Include inputPoller.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class GLFWInputPoller
	\brief Contains functions for polling input (checks current state),
	* specific to GLFW API input polling. Inherits from InputPoller class
	*/
	class GLFWInputPoller : public InputPoller
	{
	protected: // Protected members

		//! Get key pressed status (Windows API specific implementation)
		/*!
		\param keycode A integer representing the key code (if pressed)
		\return A boolean to identify whether a key was pressed or not
		*/
		virtual bool isKeyPressedImpl(int keycode) override;

		//! Get mouse button pressed status (Windows API specific implementation)
		/*!
		\param button A integer representing the mouse button (if pressed)
		\return A boolean to identify whether a mouse button was pressed or not
		*/
		virtual bool isMouseButtonPressedImpl(int button) override;

		//! Get current mouse position (Windows API specific implementation)
		/*!
		\return A vector2 showing the current mouse position (X and Y axis)
		*/
		virtual glm::vec2 getMousePositionImpl() override;

		//! Get current mouse 'X' position (Windows API specific implementation)
		/*!
		\return A float showing the current mouse position (X axis)
		*/
		virtual float getMouseXImpl() override;

		//! Get current mouse 'Y' position (Windows API specific implementation)
		/*!
		\return A float showing the current mouse position (Y axis)
		*/
		virtual float getMouseYImpl() override;

	};
}
