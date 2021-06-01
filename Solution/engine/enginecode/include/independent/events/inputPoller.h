/** \file inputPoller.h
*/

#pragma once // Compile once

#include <glm/glm.hpp> // Include glm.hpp file

#ifdef NG_PLATFORM_WINDOWS // If windows platform is defined...
#include "core/keyCodes.h" // Include keyCodes.h file
#include "core/mouseCodes.h" // Include mouseCodes.h file
#endif // End if windows platform is defined...

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class InputPoller
	\brief Contains functions for polling input (checks current state),
	* acts as an interface for GLFW input polling (currently)
	*/
	class InputPoller
	{
	private: // Private members
		static InputPoller* s_instance; //!< Raw pointer, create a 'InputPoller' class instance (singleton)

	protected: // Protected members
		//! Get key pressed status (Windows API specific implementation)
		/*!
		\param keycode A integer representing the key code (if pressed)
		\return A boolean to identify whether a key was pressed or not
		*/
		virtual bool isKeyPressedImpl(int keycode) = 0;

		//! Get mouse button pressed status (Windows API specific implementation)
		/*!
		\param button A integer representing the mouse button (if pressed)
		\return A boolean to identify whether a mouse button was pressed or not
		*/
		virtual bool isMouseButtonPressedImpl(int button) = 0;

		//! Get current mouse position (Windows API specific implementation)
		/*!
		\return A vector2 showing the current mouse position (X and Y axis)
		*/
		virtual glm::vec2 getMousePositionImpl() = 0;

		//! Get current mouse 'X' position (Windows API specific implementation)
		/*!
		\return A float showing the current mouse position (X axis)
		*/
		virtual float getMouseXImpl() = 0;

		//! Get current mouse 'Y' position (Windows API specific implementation)
		/*!
		\return A float showing the current mouse position (Y axis)
		*/
		virtual float getMouseYImpl() = 0;

	public: // Public members
		//! Get key pressed status
		/*!
		\param keycode A integer representing the key code (if pressed)
		\return A boolean to identify whether a key was pressed or not
		*/
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }

		//! Get mouse button pressed status
		/*!
		\param button A integer representing the mouse button (if pressed)
		\return A boolean to identify whether a mouse button was pressed or not
		*/
		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }

		//! Get current mouse position
		/*!
		\return A vector2 showing the current mouse position (X and Y axis)
		*/
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionImpl(); }

		//! Get current mouse 'X' position
		/*!
		\return A float showing the current mouse position (X axis)
		*/
		inline static float getMouseX() { return s_instance->getMouseXImpl(); }

		//! Get current mouse 'Y' position
		/*!
		\return A float showing the current mouse position (Y axis)
		*/
		inline static float getMouseY() { return s_instance->getMouseYImpl(); }

	};
}



