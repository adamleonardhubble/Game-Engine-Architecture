
#pragma once // Compile once

#include <gtest/gtest.h> // Include google unit testing
#include <string> // Include string support

#include "events/event.h" // Include event.h file

#include "events/windowEvent.h" // Include windowEvent.h file

#include "events/mouseEvent.h" // Include mouseEvent.h file
#include "core/mouseCodes.h" // Include mouseCodes.h file

#include "events/keyEvent.h" // Include keyEvents.h
#include "core/keyCodes.h" // Include keyCode.h

#include "platform/GLFW/GLFWWindowInputPoller.h" // Include GLFWWindowInputPoller.h file

#define private public // Define private class members public

const int Width = 1280; // Window resize width dimension
const int Height = 720; // Window resize height dimension

Engine::WindowResizeEvent windowResizeEvent(Width, Height); // Create window resize event, passing declared width and height parameters
Engine::WindowCloseEvent windowCloseEvent; // Create window close event

const float movedPositionX = 560.0f; // Window moved position in 'X' axis
const float movedPositionY = 720.0f; // Window moved position in 'Y' axis

Engine::WindowMovedEvent windowMovedEvent(movedPositionX, movedPositionY); // Create window moved event, passing window moved positions in the 'X' and 'Y' axes 

float focusPositionX = 0.0f; // Window focus position in the 'X' axis
float focusPositionY = 0.0f; // Window focus position in the 'Y' axis

Engine::WindowFocusEvent windowFocusedEvent(focusPositionX, focusPositionY); // Create window focused event, passing window focus positions in the 'X' and 'Y' axes 

float lostFocusPositionX = 0.0f; // Window lost focus position in the 'X' axis
float lostFocusPositionY = 0.0f; // Window lost focus position in the 'Y' axis

Engine::WindowLostFocusEvent windowLostFocusEvent(lostFocusPositionX, lostFocusPositionY); // Create window lost focus event, passing window lost focus positions in the 'X' and 'Y' axes 

const int mouseButtonOne = ENGINE_MOUSE_BUTTON_1; // Mouse button one (pressed)
const int mouseButtonTwo = ENGINE_MOUSE_BUTTON_2; // Mouse button one (released)

Engine::MouseButtonPressedEvent mouseButtonPressedEvent(mouseButtonOne); // Create mouse button pressed event, passing mouse button one (pressed)
Engine::MouseButtonReleasedEvent mouseButtonReleasedEvent(mouseButtonTwo); // Create mouse button released event, passing mouse button two (released)

const int keyTyped = ENGINE_KEY_P; // Key typed (pressed) key code
const int keyPressedOne = ENGINE_KEY_P; // Key pressed one key code
const int keyPressedTwo = ENGINE_KEY_P; // Key pressed two key code
const int keyRepeatCount = 0; // Key pressed repeat count 

Engine::KeyTypedEvent keyTypedEvent(keyTyped); // Create key typed event, passing the key pressed
Engine::KeyPressedEvent keyPressedEvent(keyPressedOne, keyRepeatCount); // Create key pressed event, passing key pressed and key pressed repeat count (pressed)
Engine::KeyReleasedEvent keyReleasedEvent(keyPressedTwo); // Create key released event, passing key released (released)

const float inputAxisX = 75.54f; // Input mouse position in the 'X' axis
const float inputAxisY = 420.45f; // Input mouse position in the 'Y' axis

Engine::MouseMovedEvent mouseMovedEvent(inputAxisX, inputAxisY); // Create mouse moved event, passing the mouse positions in the 'X' and 'Y' axes

float inputScrollOffsetAxisX = 57.23f; // Input mouse scroll offset in the 'X' axis
float inputScrollOffsetAxisY = 68.59f; // Input mouse scroll offset in the 'Y' axis

Engine::MouseScrolledEvent mouseScrolledEvent(inputScrollOffsetAxisX, inputScrollOffsetAxisY); // Create mouse scrolled event, passing the mouse scroll offsets in the 'X' and 'Y' axes

bool onWindowResizeTrue(Engine::WindowResizeEvent& e) // Create boolean function, returning true for a passed window resize event
{
	return true; // Return true
}

bool onWindowResizeFalse(Engine::WindowResizeEvent& e) // Create boolean function, returning false for a passed window resize event
{
	return false; // Return false
}

bool onWindowCloseTrue(Engine::WindowCloseEvent& e) // Create boolean, function, returning true for a passed window close event
{
	return true; // Return true
}

bool onWindowCloseFalse(Engine::WindowCloseEvent& e) // Create boolean, function, returning false for a passed window close event
{
	return false; // Return false
}

bool onWindowMovedTrue(Engine::WindowMovedEvent& e) // Create boolean, function, returning true for a passed window moved event
{
	return true; // Return true
}

bool onWindowMovedFalse(Engine::WindowMovedEvent& e) // Create boolean, function, returning false for a passed window moved event
{
	return false; // Return false
}

bool onWindowFocusedTrue(Engine::WindowFocusEvent& e) // Create boolean, function, returning true for a passed window focused event
{
	return true; // Return true
}

bool onWindowFocusedFalse(Engine::WindowFocusEvent& e) // Create boolean, function, returning false for a passed window focused event
{
	return false; // Return false
}

bool onWindowLostFocusTrue(Engine::WindowLostFocusEvent& e) // Create boolean, function, returning true for a passed window lost focus event
{
	return true; // Return true
}

bool onWindowLostFocusFalse(Engine::WindowLostFocusEvent& e) // Create boolean, function, returning false for a passed window lost focus event
{
	return false; // Return false
}

bool onMouseMovedTrue(Engine::MouseMovedEvent& e) // Create boolean, function, returning true for a passed mouse moved event
{
	return true; // Return true
}

bool onMouseMovedFalse(Engine::MouseMovedEvent& e) // Create boolean, function, returning false for a passed mouse moved event
{
	return false; // Return false
}

bool onMouseScrolledTrue(Engine::MouseScrolledEvent& e) // Create boolean, function, returning true for a passed mouse scrolled event
{
	return true; // Return true
}

bool onMouseScrolledFalse(Engine::MouseScrolledEvent& e) // Create boolean, function, returning false for a passed mouse scrolled event
{
	return false; // Return false
}

bool onMouseButtonPressedTrue(Engine::MouseButtonPressedEvent& e) // Create boolean, function, returning true for a passed mouse button pressed event
{
	return true; // Return true
}

bool onMouseButtonPressedFalse(Engine::MouseButtonPressedEvent& e) // Create boolean, function, returning false for a passed mouse button pressed event
{
	return false; // Return false
}

bool onMouseButtonReleasedTrue(Engine::MouseButtonReleasedEvent& e) // Create boolean, function, returning true for a passed mouse button released event
{
	return true; // Return true
}

bool onMouseButtonReleasedFalse(Engine::MouseButtonReleasedEvent& e) // Create boolean, function, returning false for a passed mouse button released event
{
	return false; // Return false
}

bool onKeyPressedTrue(Engine::KeyPressedEvent& e) // Create boolean, function, returning true for a passed key pressed event
{
	return true; // Return true
}

bool onKeyPressedFalse(Engine::KeyPressedEvent& e) // Create boolean, function, returning false for a passed key pressed event
{
	return false; // Return false
}

bool onKeyReleasedTrue(Engine::KeyReleasedEvent& e) // Create boolean, function, returning true for a passed key released event
{
	return true; // Return true
}

bool onKeyReleasedFalse(Engine::KeyReleasedEvent& e) // Create boolean, function, returning false for a passed key released event
{
	return false; // Return false
}