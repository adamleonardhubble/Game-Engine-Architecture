
#include "eventTests.h" // Include eventTests.h file

////////////////////////////////////////////////////////////////
///////// Window and event dispatch-related test cases /////////
////////////////////////////////////////////////////////////////

TEST(Events, WindowResizeConstructor) // Resize window with new dimensions (Width, Height), check if set in event
{
	int getWidth = windowResizeEvent.getWidth(); // Set getWidth to the window width
	int getHeight = windowResizeEvent.getHeight(); // Set getHeight to the window height

	EXPECT_EQ(getWidth, Width); // Expect window dimensions to be the dimensions set in the event
	EXPECT_EQ(getHeight, Height); // Expect window dimensions to be the dimensions set in the event
}

TEST(Events, DispatchWindowResizeTrue) // Dispatch window resize event, as the event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(windowResizeEvent); // Dispatch window resize event
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(onWindowResizeTrue, std::placeholders::_1)); // Return whether window resize event has been dispatched

	EXPECT_TRUE(result); // Expect true, a window resize event was dispatched
}

TEST(Events, DispatchWindowResizeFalse) // Dispatch window close event instead of resize event, window resize event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowCloseEvent); // Dispatch window close event
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(onWindowResizeTrue, std::placeholders::_1)); // Return whether window resize event has been dispatched

	EXPECT_FALSE(result); // Expect false, no window resize event was dispatched
}

TEST(Events, DispatchWindowResizeHandleTrue) // Dispatch window resize event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(windowResizeEvent); // Dispatch window resize event
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(onWindowResizeTrue, std::placeholders::_1)); // Determine whether window resize event was dispatched
	bool result = windowResizeEvent.bEventHandled(); // Check if a window resize event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a window resize event was handled as a window resize event and was dispatched
}

TEST(Events, DispatchWindowResizeHandleFalse) // Dispatch window resize event, window resize event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowResizeEvent); // Dispatch window resize event
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(onWindowResizeFalse, std::placeholders::_1)); // Determine whether window resize event was dispatched 
	bool result = windowResizeEvent.bEventHandled(); // Check if a window resize event was handled (not dispatched)

	EXPECT_FALSE(result); // Expect false, no window resize event was handled and a window resize event was not dispatched
}

TEST(Events, DispatchWindowCloseTrue) // Dispatch window close event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(windowCloseEvent); // Dispatch window close event
	bool result = dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(onWindowCloseTrue, std::placeholders::_1)); // Return whether window close event has been dispatched

	EXPECT_TRUE(result); // Expect true, a window close event was dispatched
}

TEST(Events, DispatchWindowCloseFalse) // Dispatch window resize event instead of close event, window close event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowResizeEvent); // Dispatch window resize event
	bool result = dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(onWindowCloseTrue, std::placeholders::_1)); // Return whether window close event has been dispatched

	EXPECT_FALSE(result); // Expect false, no window close event was dispatched
}

TEST(Events, DispatchWindowCloseHandleTrue) // Dispatch window close event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(windowCloseEvent); // Dispatch window close event
	dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(onWindowCloseTrue, std::placeholders::_1)); // Determine whether window close event was dispatched
	bool result = windowCloseEvent.bEventHandled(); // Check if a window close event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a window close event was handled and a window close event was dispatched
}

TEST(Events, DispatchWindowCloseHandleFalse) // Dispatch window close event, window close event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowCloseEvent); // Dispatch window close event
	dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(onWindowCloseFalse, std::placeholders::_1)); // Determine whether window close event was dispatched
	bool result = windowCloseEvent.bEventHandled(); // Check if a window close event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no window close event was handled and a window close event was not dispatched
}

TEST(Events, WindowMovedConstructor) // Move window with new positions (X axis, Y axis), check if set in event
{
	float getPositionX = windowMovedEvent.getWindowPositionX(); // Set getPositionX to the returning window position in the 'X' axis
	float getPositionY = windowMovedEvent.getWindowPositionY(); // Set getPositionY to the returning window position in the 'Y' axis

	EXPECT_EQ(getPositionX, movedPositionX); // Expect the input window moved position set in the 'X' axis to be equal to the returned window position in the 'X' axis
	EXPECT_EQ(getPositionY, movedPositionY); // Expect the input window moved position set in the 'Y' axis to be equal to the returned window position in the 'Y' axis
}

TEST(Events, DispatchWindowMovedTrue) // Dispatch window moved event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(windowMovedEvent); // Dispatch window moved event
	bool result = dispatcher.dispatch<Engine::WindowMovedEvent>(std::bind(onWindowMovedTrue, std::placeholders::_1)); // Return whether window moved event has been dispatched

	EXPECT_TRUE(result); // Expect true, a window moved event was dispatched
}

TEST(Events, DispatchWindowMovedFalse) // Dispatch window close event instead of moved event, window moved event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowCloseEvent); // Dispatch window close event
	bool result = dispatcher.dispatch<Engine::WindowMovedEvent>(std::bind(onWindowMovedTrue, std::placeholders::_1)); // Return whether window moved event has been dispatched

	EXPECT_FALSE(result); // Expect false, no window moved event was dispatched
}

TEST(Events, DispatchWindowMovedHandleTrue) // Dispatch window moved event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(windowMovedEvent); // Dispatch window moved event
	dispatcher.dispatch<Engine::WindowMovedEvent>(std::bind(onWindowMovedTrue, std::placeholders::_1)); // Determine whether window moved event was dispatched
	bool result = windowMovedEvent.bEventHandled(); // Check if a window moved event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a window moved event was handled and a window moved event was dispatched
}

TEST(Events, DispatchWindowMovedHandleFalse) // Dispatch window moved event, window moved event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowMovedEvent); // Dispatch window moved event
	dispatcher.dispatch<Engine::WindowMovedEvent>(std::bind(onWindowMovedFalse, std::placeholders::_1)); // Determine whether window moved event was dispatched
	bool result = windowMovedEvent.bEventHandled(); // Check if a window moved event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no window moved event was handled and a window moved event was not dispatched
}

TEST(Events, DispatchWindowFocusTrue) // Dispatch window focus event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(windowFocusedEvent); // Dispatch window focus event
	bool result = dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onWindowFocusedTrue, std::placeholders::_1)); // Return whether window focus event has been dispatched

	EXPECT_TRUE(result); // Expect true, a window focus event was dispatched
}

TEST(Events, DispatchWindowFocusFalse) // Dispatch window moved event instead of focus event, window focus event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowMovedEvent); // Dispatch window moved event
	bool result = dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onWindowFocusedTrue, std::placeholders::_1)); // Return whether window focus event has been dispatched

	EXPECT_FALSE(result); // Expect false, no window focus event was dispatched
}

TEST(Events, DispatchWindowFocusedHandleTrue) // Dispatch window focus event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(windowFocusedEvent); // Dispatch window focus event
	dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onWindowFocusedTrue, std::placeholders::_1)); // Determine whether window focus event was dispatched
	bool result = windowFocusedEvent.bEventHandled(); // Check if a window focus event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a window focus event was handled and a window focus event was dispatched
}

TEST(Events, DispatchWindowFocusedHandleFalse) // Dispatch window focus event, window focus event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowFocusedEvent); // Dispatch window focus event
	dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onWindowFocusedFalse, std::placeholders::_1)); // Determine whether window focus event was dispatched
 
	bool result = windowFocusedEvent.bEventHandled(); // Check if a window focus event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no window focus event was handled and a window focus event was not dispatched
}

TEST(Events, DispatchWindowLostFocusTrue) // Dispatch window lost focus event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(windowLostFocusEvent); // Dispatch window lost focus event
	bool result = dispatcher.dispatch<Engine::WindowLostFocusEvent>(std::bind(onWindowLostFocusTrue, std::placeholders::_1)); // Return whether window lost focus event has been dispatched

	EXPECT_TRUE(result); // Expect true, a window lost focus event was dispatched
}

TEST(Events, DispatchWindowLostFocusFalse) // Dispatch window resize event instead of lost focus event, window lost focus event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowResizeEvent); // Dispatch window resize event
	bool result = dispatcher.dispatch<Engine::WindowLostFocusEvent>(std::bind(onWindowLostFocusTrue, std::placeholders::_1)); // Return whether window lost focus event has been dispatched

	EXPECT_FALSE(result); // Expect false, no window lost focus event was dispatched
}

TEST(Events, DispatchWindowLostFocusHandleTrue) // Dispatch window lost focus event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(windowLostFocusEvent); // Dispatch window lost focus event
	dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onWindowFocusedTrue, std::placeholders::_1)); // Determine whether window lost focus event was dispatched
	bool result = windowLostFocusEvent.bEventHandled(); // Check if a window lost focus event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a window lost focus event was handled and a window lost focus event was dispatched
}

TEST(Events, DispatchWindowLostFocusHandleFalse) // Dispatch window lost focus event, window lost focus event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowLostFocusEvent); // Dispatch window lost focus event
	dispatcher.dispatch<Engine::WindowLostFocusEvent>(std::bind(onWindowLostFocusFalse, std::placeholders::_1)); // Determine whether window lost focus event was dispatched

	bool result = windowLostFocusEvent.bEventHandled(); // Check if a window lost focus event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no window lost focus event was handled and a window lost 
}

TEST(Events, DispatchMouseMovedTrue) // Dispatch mouse moved event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(mouseMovedEvent); // Dispatch mouse moved event
	bool result = dispatcher.dispatch<Engine::MouseMovedEvent>(std::bind(onMouseMovedTrue, std::placeholders::_1)); // Return whether mouse moved event has been dispatched

	EXPECT_TRUE(result); // Expect true, a mouse moved event was dispatched
}

TEST(Events, DispatchMouseMovedFalse) // Dispatch window moved event instead of mouse moved event, mouse moved event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(windowMovedEvent); // Dispatch window moved event
	bool result = dispatcher.dispatch<Engine::MouseMovedEvent>(std::bind(onMouseMovedTrue, std::placeholders::_1)); // Return whether mouse moved event has been dispatched

	EXPECT_FALSE(result); // Expect false, no mouse moved event was dispatched
}

TEST(Events, DispatchMouseMovedHandleTrue) // Dispatch mouse moved event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(mouseMovedEvent); // Dispatch mouse moved event
	dispatcher.dispatch<Engine::MouseMovedEvent>(std::bind(onMouseMovedTrue, std::placeholders::_1)); // Determine whether mouse moved event was dispatched
	bool result = mouseMovedEvent.bEventHandled(); // Check if a mouse moved event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a mouse moved event was handled and a mouse moved event was dispatched
}

TEST(Events, DispatchMouseMovedHandleFalse) // Dispatch mouse moved event, mouse moved event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseMovedEvent); // Dispatch mouse moved event
	dispatcher.dispatch<Engine::MouseMovedEvent>(std::bind(onMouseMovedFalse, std::placeholders::_1)); // Determine whether mouse moved event was dispatched

	bool result = mouseMovedEvent.bEventHandled(); // Check if a mouse moved event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no mouse moved event was handled and a mouse moved event was not dispatched
}

TEST(Events, DispatchMouseScrolledTrue) // Dispatch mouse scrolled event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(mouseScrolledEvent); // Dispatch mouse scrolled event
	bool result = dispatcher.dispatch<Engine::MouseScrolledEvent>(std::bind(onMouseScrolledTrue, std::placeholders::_1)); // Return whether mouse scrolled event has been dispatched

	EXPECT_TRUE(result); // Expect true, a mouse scrolled event was dispatched
}

TEST(Events, DispatchMouseScrolledFalse) // Dispatch mouse moved event instead of mouse scrolled event, mouse scrolled event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseMovedEvent); // Dispatch mouse moved event
	bool result = dispatcher.dispatch<Engine::MouseScrolledEvent>(std::bind(onMouseScrolledTrue, std::placeholders::_1)); // Return whether mouse scrolled event has been dispatched

	EXPECT_FALSE(result); // Expect false, no mouse scrolled event was dispatched
}

TEST(Events, DispatchMouseScrolledHandleTrue) // Dispatch mouse scrolled event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(mouseScrolledEvent); // Dispatch mouse scrolled event
	dispatcher.dispatch<Engine::MouseScrolledEvent>(std::bind(onMouseScrolledTrue, std::placeholders::_1)); // Determine whether mouse scrolled event was dispatched
	bool result = mouseScrolledEvent.bEventHandled(); // Check if a mouse scrolled event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a mouse scrolled event was handled and a mouse moved event was dispatched
}

TEST(Events, DispatchMouseScrolledHandleFalse) // Dispatch mouse scrolled event, mouse scrolled event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseScrolledEvent); // Dispatch mouse scrolled event
	dispatcher.dispatch<Engine::MouseScrolledEvent>(std::bind(onMouseScrolledFalse, std::placeholders::_1)); // Determine whether mouse scrolled event was dispatched

	bool result = mouseScrolledEvent.bEventHandled(); // Check if a mouse scrolled event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no mouse scrolled event was handled and a mouse scrolled event was not dispatched
}

TEST(Events, DispatchMouseButtonPressedTrue) // Dispatch mouse button pressed event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(mouseButtonPressedEvent); // Dispatch mouse button pressed event
	bool result = dispatcher.dispatch<Engine::MouseButtonPressedEvent>(std::bind(onMouseButtonPressedTrue, std::placeholders::_1)); // Return whether mouse button pressed event has been dispatched

	EXPECT_TRUE(result); // Expect true, a mouse button pressed event was dispatched
}

TEST(Events, DispatchMouseButtonPressedFalse) // Dispatch mouse scrolled event instead of mouse button pressed event, mouse button pressed event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseScrolledEvent); // Dispatch mouse scrolled event
	bool result = dispatcher.dispatch<Engine::MouseButtonPressedEvent>(std::bind(onMouseButtonPressedTrue, std::placeholders::_1)); // Return whether mouse button pressed event has been dispatched

	EXPECT_FALSE(result); // Expect false, no mouse button pressed event was dispatched
}

TEST(Events, DispatchMouseButtonPressedHandleTrue) // Dispatch mouse button pressed event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(mouseButtonPressedEvent); // Dispatch mouse button pressed event
	dispatcher.dispatch<Engine::MouseButtonPressedEvent>(std::bind(onMouseButtonPressedTrue, std::placeholders::_1)); // Determine whether mouse button pressed event was dispatched
	bool result = mouseButtonPressedEvent.bEventHandled(); // Check if a mouse button pressed event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a mouse button pressed event was handled and a mouse button pressed event was dispatched
}

TEST(Events, DispatchMouseButtonPressedHandleFalse) // Dispatch mouse button pressed event, mouse button pressed event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseButtonPressedEvent); // Dispatch mouse button pressed event
	dispatcher.dispatch<Engine::MouseButtonPressedEvent>(std::bind(onMouseButtonPressedFalse, std::placeholders::_1)); // Determine whether mouse button pressed event was dispatched

	bool result = mouseButtonPressedEvent.bEventHandled(); // Check if a mouse button pressed event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no mouse button pressed event was handled and a mouse button pressed event was not dispatched
}

TEST(Events, DispatchMouseButtonReleasedTrue) // Dispatch mouse button released event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(mouseButtonReleasedEvent); // Dispatch mouse button released event
	bool result = dispatcher.dispatch<Engine::MouseButtonReleasedEvent>(std::bind(onMouseButtonReleasedTrue, std::placeholders::_1)); // Return whether mouse button released event has been dispatched

	EXPECT_TRUE(result); // Expect true, a mouse button released event was dispatched
}

TEST(Events, DispatchMouseButtonReleasedFalse) // Dispatch mouse button pressed event instead of mouse button released event, mouse button released event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseButtonPressedEvent); // Dispatch mouse button pressed event
	bool result = dispatcher.dispatch<Engine::MouseButtonReleasedEvent>(std::bind(onMouseButtonReleasedTrue, std::placeholders::_1)); // Return whether mouse button released event has been dispatched

	EXPECT_FALSE(result); // Expect false, no mouse button released event was dispatched
}

TEST(Events, DispatchMouseButtonReleasedHandleTrue) // Dispatch mouse button released event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(mouseButtonReleasedEvent); // Dispatch mouse button released event
	dispatcher.dispatch<Engine::MouseButtonReleasedEvent>(std::bind(onMouseButtonReleasedTrue, std::placeholders::_1)); // Determine whether mouse button released event was dispatched
	bool result = mouseButtonReleasedEvent.bEventHandled(); // Check if a mouse button released event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a mouse button released event was handled and a mouse button released event was dispatched
}

TEST(Events, DispatchMouseButtonReleasedHandleFalse) // Dispatch mouse button released event, mouse button released event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseButtonReleasedEvent); // Dispatch mouse button released event
	dispatcher.dispatch<Engine::MouseButtonReleasedEvent>(std::bind(onMouseButtonReleasedFalse, std::placeholders::_1)); // Determine whether mouse button released event was dispatched

	bool result = mouseButtonReleasedEvent.bEventHandled(); // Check if a mouse button released event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no mouse button released event was handled and a mouse button released event was not dispatched
}

TEST(Events, DispatchKeyPressedTrue) // Dispatch key pressed event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(keyPressedEvent); // Dispatch key pressed event
	bool result = dispatcher.dispatch<Engine::KeyPressedEvent>(std::bind(onKeyPressedTrue, std::placeholders::_1)); // Return whether key pressed event has been dispatched

	EXPECT_TRUE(result); // Expect true, a key pressed event was dispatched
}

TEST(Events, DispatchKeyPressedFalse) // Dispatch mouse button released event instead of key pressed event, key pressed event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(mouseButtonReleasedEvent); // Dispatch mouse button released event
	bool result = dispatcher.dispatch<Engine::KeyPressedEvent>(std::bind(onKeyPressedTrue, std::placeholders::_1)); // Return whether key pressed event has been dispatched

	EXPECT_FALSE(result); // Expect false, no key pressed event was dispatched
}

TEST(Events, DispatchKeyPressedHandleTrue) // Dispatch key pressed event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(keyPressedEvent); // Dispatch key pressed event
	dispatcher.dispatch<Engine::KeyPressedEvent>(std::bind(onKeyPressedTrue, std::placeholders::_1)); // Determine whether key pressed event was dispatched
	bool result = keyPressedEvent.bEventHandled(); // Check if a key pressed event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a key pressed event was handled and a key pressed event was dispatched
}

TEST(Events, DispatchKeyPressedHandleFalse) // Dispatch key pressed event, key pressed event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(keyPressedEvent); // Dispatch key pressed event
	dispatcher.dispatch<Engine::KeyPressedEvent>(std::bind(onKeyPressedFalse, std::placeholders::_1)); // Determine whether key pressed event was dispatched

	bool result = keyPressedEvent.bEventHandled(); // Check if a key pressed event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no key pressed event was handled and a key pressed event was not dispatched
}

TEST(Events, DispatchKeyReleasedTrue) // Dispatch key released event, as event gets dispatched expect true
{
	Engine::EventDispatcher dispatcher(keyReleasedEvent); // Dispatch key released event
	bool result = dispatcher.dispatch<Engine::KeyReleasedEvent>(std::bind(onKeyReleasedTrue, std::placeholders::_1)); // Return whether key released event has been dispatched

	EXPECT_TRUE(result); // Expect true, a key released event was dispatched
}

TEST(Events, DispatchKeyReleasedFalse) // Dispatch key pressed event instead of key released event, key released event does not get dispatched, therefore false is expected
{
	Engine::EventDispatcher dispatcher(keyPressedEvent); // Dispatch key pressed event
	bool result = dispatcher.dispatch<Engine::KeyReleasedEvent>(std::bind(onKeyReleasedTrue, std::placeholders::_1)); // Return whether key released event has been dispatched

	EXPECT_FALSE(result); // Expect false, no key released event was dispatched
}

TEST(Events, DispatchKeyReleasedHandleTrue) // Dispatch key released event, as the event gets dispatched and handled expect true
{
	Engine::EventDispatcher dispatcher(keyReleasedEvent); // Dispatch key released event
	dispatcher.dispatch<Engine::KeyReleasedEvent>(std::bind(onKeyReleasedTrue, std::placeholders::_1)); // Determine whether key released event was dispatched
	bool result = keyReleasedEvent.bEventHandled(); // Check if a key released event was handled (dispatched)

	EXPECT_TRUE(result); // Expect true, a key released event was handled and a key released event was dispatched
}

TEST(Events, DispatchKeyReleasedHandleFalse) // Dispatch key released event, key released event does not get dispatched or handled, therefore false is expected
{
	Engine::EventDispatcher dispatcher(keyReleasedEvent); // Dispatch key released event
	dispatcher.dispatch<Engine::KeyReleasedEvent>(std::bind(onKeyReleasedFalse, std::placeholders::_1)); // Determine whether key released event was dispatched

	bool result = keyReleasedEvent.bEventHandled(); // Check if a key released event was handled (dispatched)

	EXPECT_FALSE(result); // Expect false, no key released event was handled and a key released event was not dispatched
}

////////////////////////////////////////////////////////////////
/////////////////// Input-related test cases ///////////////////
////////////////////////////////////////////////////////////////

TEST(Events, MouseButtonPressedAndReleasedConstructor) // Mouse button is pressed and released, therefore key code values expect to be equal
{
	int getButtonPressed = mouseButtonPressedEvent.getMouseButton(); // Set getButtonPressed to a mouse button pressed event button
	int getButtonReleased = mouseButtonReleasedEvent.getMouseButton(); // Set getButtonReleased to a mouse button released event button

	EXPECT_EQ(getButtonPressed, mouseButtonOne); // Expect the mouse button pressed to be mouse button one
	EXPECT_EQ(getButtonReleased, mouseButtonTwo); // Expect the mouse button released to be mouse button two
}

TEST(Events, KeyPressedAndReleasedConstructor) // Key is pressed and released, therefore key code values of the key typed, pressed and released expect to be equal
{
	int getKeyTyped = keyTypedEvent.getKeyCode(); // Set getKeyTyped to a key typed event key code
	int getKeyPressed = keyPressedEvent.getKeyCode(); // Set getKeyPressed to a key pressed event key code
	int getKeyReleased = keyReleasedEvent.getKeyCode(); // Set getKeyReleased to a key released event key code

	EXPECT_EQ(getKeyTyped, keyPressedOne); // Expect the key typed key code to be the key pressed button
	EXPECT_EQ(getKeyPressed, keyPressedOne); // Expect the key pressed key code to be the key code of keyPressedOne
	EXPECT_EQ(getKeyReleased, keyPressedTwo); // Expect the key released key code to be the key code of keyPressedTwo
}

TEST(Events, MouseMovedEventConstructor) // Mouse is moved to given coordinates, therefore the given coordinates and returned coordinates should expect to be equal
{
	float getMousePositionX = mouseMovedEvent.getMousePositionX(); // Set getMousePositionX to the returning mouse position in the 'X' axis
	float getMousePositionY = mouseMovedEvent.getMousePositionY(); // Set getMousePositionX to the returning mouse position in the 'Y' axis

	EXPECT_EQ(getMousePositionX, inputAxisX); // Expect the input mouse position in the 'X' axis to be equal to the returned mouse position in the 'X' axis
	EXPECT_EQ(getMousePositionY, inputAxisY); // Expect the input mouse position in the 'Y' axis to be equal to the returned mouse position in the 'Y' axis
}

TEST(Events, MouseScrolledEventConstructor) // Mouse is scrolled to given coordinates, therefore the given coordinates and expected coordinates should expect to be equal
{
	float getMouseScrollOffsetX = mouseScrolledEvent.getXOffset(); // Set getMouseScrollOffsetX to the returning mouse scroll offset in the 'X' axis
	float getMouseScrollOffsetY = mouseScrolledEvent.getYOffset(); // Set getMouseScrollOffsetY to the returning mouse scroll offset in the 'Y' axis

	EXPECT_EQ(getMouseScrollOffsetX, inputScrollOffsetAxisX); // Expect the input mouse scroll offset in the 'X' axis to be equal to the returned mouse scroll offset in the 'X' axis
	EXPECT_EQ(getMouseScrollOffsetY, inputScrollOffsetAxisY); // Expect the input mouse scroll offset in the 'Y' axis to be equal to the returned mouse scroll offset in the 'Y' axis
}

