/** \file GLFWWindowImplementation.cpp
*/

#include "engine_pch.h" // Include precompiled headers file

#include "systems/log.h" // Include log.h file

#include <glad/glad.h> // Include glad.h file

#include "platform/glfw/GLFWWindowImplementation.h" // Include GLFWWindowImplementation.h file

namespace Engine // Engine namespace
{
	Window* Window::create(const WindowProperties& properties) // Function, create a window passing window properties
	{
		return new GLFWWindowImpl(properties); // Return a new instance of a window with set properties (set in init())
	}

	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties& properties) // Constructor, initialise GLFW window with passed properties
	{
		init(properties); // Set window properties to init() window properites
	}

	GLFWWindowImpl::~GLFWWindowImpl() // Destructor
	{
		close(); // Call function, close (window closes)

		m_nativeWindow = nullptr; // Set 'm_nativeWindow' to nullptr when application terminates
	}

	void GLFWWindowImpl::init(const WindowProperties& properties) // Function, intialise window with passed properties (open)
	{
		m_properties.m_title = properties.m_title; // Set WindowProperties struct 'title' value to the window title, when intialised
		m_properties.m_width = properties.m_width; // Set WindowProperties struct 'width' value to the window width, when intialised
		m_properties.m_height = properties.m_height; // Set WindowProperties struct 'height' value to the window height, when intialised

		ENGINE_INFO("Window created: {0}, Width: {1}, Height {2}", m_properties.m_title, m_properties.m_width, m_properties.m_height); // Ouput 'info' type to logger console window, display window created with its given window properties (default)

		m_nativeWindow = glfwCreateWindow((int)m_properties.m_width, (int)m_properties.m_height, m_properties.m_title.c_str(), nullptr, nullptr); // Create window, set to native window (pointer) with the given window properties

		m_context = std::shared_ptr<GLFWGraphicsContext>(new GLFWGraphicsContext(m_nativeWindow)); // Set GLFW graphics context (pointer) to the native window (pointer)
		m_context->init(); // Initialise GLFW graphics context (pointer)

		glfwSetWindowUserPointer(m_nativeWindow, &m_callback); // Set the windows user data to the callback (set the user pointer of the window)

		setVSync(true); // Enable vSync, set 'true'

		#pragma region Set GLFW callback functions, relative to event types (window, key and mouse)
		glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height) // Function, set the window size callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			WindowResizeEvent event(width, height); // Create a window resize event, passing new dimensions
			callback(event); // Callback processes window resize event to event dispatcher (binded to)
		});

		glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window) // Function, set the window close callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			WindowCloseEvent event; // Create a window close event
			callback(event); // Callback processes window close event to event dispatcher (binded to)
		});

		glfwSetWindowPosCallback(m_nativeWindow, [](GLFWwindow* window, int positionX, int positionY) // Function, set the window moved callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			WindowMovedEvent event(positionX, positionY); // Create a window moved event, passing new positions
			callback(event); // Callback processes window moved event to event dispatcher (binded to)
		});

		glfwSetWindowFocusCallback(m_nativeWindow, [](GLFWwindow* window, int focused) // Function, set the window focus callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			if (focused == GLFW_TRUE) // If the window is focused, do the following
			{
				WindowFocusEvent event(0, 0); // Create a window focus event
				callback(event); // Callback processes window focus event to event dispatcher (binded to)
			}
			if (focused == GLFW_FALSE) // If the window is not focused (lost), do the following
			{
				WindowLostFocusEvent event(0, 0); // Create a window lost focus event
				callback(event); // Callback processes window lost focus event to event dispatcher (binded to)
			}
		});

		glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) // Function, set the key callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			switch (action) // Switch statement, if a key is 'pressed', 'released' or 'repeated'
			{
			case ENGINE_KEY_PRESS: // When a key is pressed
			{
				KeyPressedEvent event(key, 0); // Create a key pressed event, taking the key code of the key pressed and no repeat count
				callback(event); // Callback processes key pressed event to event dispatcher (binded to)
				break; // Break from the switch statement (after event dispatch)
			}
			case ENGINE_KEY_RELEASE: // When a key is released
			{
				KeyReleasedEvent event(key); // Create a key released event, taking the key code of the key released
				callback(event); // Callback processes key released event to event dispatcher (binded to)
				break; // Break from the switch statement (after event dispatch)
			}
			case ENGINE_KEY_REPEAT: // When a key is repeated (held pressed)
			{
				KeyPressedEvent event(key, 1); // Create a key pressed event, taking the key code of the key pressed and its repeat count
				callback(event); // Callback processes key pressed event (repeat) to event dispatcher (binded to)
				break; // Break from the switch statement (after event dispatch)
			}
			}
		});

		glfwSetCharCallback(m_nativeWindow, [](GLFWwindow* window, unsigned int keycode) // Function, set the character (unicode) callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			KeyTypedEvent event(keycode); // Create a key typed event, taking the key code of the key typed
			callback(event); // Callback processes key typed event to event dispatcher (binded to)
		});

		glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods) // Function, set the mouse button callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			switch (action) // Switch statement, if a mouse button is 'pressed' or 'released'
			{
			case ENGINE_KEY_PRESS: // When a mouse button is pressed
			{
				MouseButtonPressedEvent event(button); // Create a mouse button pressed event, taking the button code of the mouse button pressed
				callback(event); // Callback processes mouse button pressed event to event dispatcher (binded to)
				break; // Break from the switch statement (after event dispatch)
			}
			case ENGINE_KEY_RELEASE: // When a mouse button is released
			{
				MouseButtonReleasedEvent event(button); // Create a mouse button released event, taking the button code of the mouse button released
				callback(event); // Callback processes mouse button released event to event dispatcher (binded to)
				break; // Break from the switch statement (after event dispatch)
			}
			}
		});

		glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset) // Function, set the mouse scroll callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			MouseScrolledEvent event((float)xOffset, (float)yOffset); // Create a mouse scrolled event, passing the scroll offsets in both 'X' and 'Y' axis
			callback(event); // Callback processes mouse scrolled event to event dispatcher (binded to)
		});

		glfwSetCursorPosCallback(m_nativeWindow, [](GLFWwindow* window, double xPosition, double yPosition) // Function, set the mouse position callback of the window
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window); // Set callback function to the windows user data

			MouseMovedEvent event((float)xPosition, (float)yPosition); // Create a mouse moved event, passing the cursor position in both 'X' and 'Y' axis
			callback(event); // Callback processes mouse moved event to event dispatcher (binded to)
		});
		#pragma endregion
	}

	void GLFWWindowImpl::close() // Function, destroy GLFW window when closed
	{
		glfwDestroyWindow(m_nativeWindow); // Destroy the window, when window is closed (exited [X])
	}

	void GLFWWindowImpl::setEventCallback(const std::function<void(Event&)> & callback) // Function, pass the passed event to event dispatcher(handles)
	{
		m_callback = callback; // Set the event callback, to the callback function
	}

	void GLFWWindowImpl::onUpdate(float timestep) // Function, update the window with passed timestep (time passed)
	{
		glfwPollEvents(); // GLFW polls events (check current status)
		m_context->swapBuffers(); // Swap buffers for GLFW graphics context

		#pragma region Viewport pillar box and letter box, when window resized
		int m_currentWindowWidth; // Integer variable, get the windows current width dimension
		int m_currentWindowHeight; // Integer variable, get the windows current height dimension

		float windowWidth; // Float variable, get the current window width dimensions (casted to a float)
		float windowHeight; // Float variable, get the current window height dimensions (casted to a float)

		int m_viewportPositionX = 0; // Integer variable, set the viewports position in the 'X' axis relative to the window (default)
		int m_viewportPositionY = 0; // Integer variable, set the viewports position in the 'Y' axis relative to the window (default)

		glfwGetFramebufferSize(m_nativeWindow, &m_currentWindowWidth, &m_currentWindowHeight); // Return the current window dimensions of the window passed

		windowWidth = (float)m_currentWindowWidth; // Set windowWidth to the window's current width dimension (casted to a float for accurate calculation of window aspect ratio)
		windowHeight = (float)m_currentWindowHeight; // Set windowHeight to the window's current height dimension (casted to a float for accurate calculation of window aspect ratio)

		m_viewportWidth = windowWidth; // Set the viewport width dimension to the current window width dimension (used to intialise viewport)
		m_viewportHeight = windowHeight; // Set the viewport height dimension to the current window height dimension (used to intialise viewport)

		// If the window width is larger than the window height when multiplied by the window aspect ratio, do the following
		if (windowWidth > windowHeight * m_properties.m_aspectRatio) // Pillar box effect
		{
			m_viewportWidth = windowHeight * m_properties.m_aspectRatio; // Set the viewport width dimension to the current window height dimension, multiplied by the window apsect ratio

			m_viewportPositionX = (windowWidth - m_viewportWidth) / 2; // Set the viewports position in the 'X' axis to the current window width dimension, minus the viewports width dimensions (halved)
		}

		// If the window height is larger than the window width when divided by the window aspect ratio, do the following
		if (windowHeight > windowWidth / m_properties.m_aspectRatio) // Letter box effect
		{
			m_viewportHeight = windowWidth / m_properties.m_aspectRatio; // Set the viewport height dimension to the current window width dimension, divided by the window apsect ratio

			m_viewportPositionY = (windowHeight - m_viewportHeight) / 2; // Set the viewports position in the 'Y' axis to the current window height dimension, minus the viewports height dimensions (halved)
		}

		glViewport(m_viewportPositionX, m_viewportPositionY, m_viewportWidth, m_viewportHeight); // Set viewport to the relative window, passing position and dimension parameters

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Window clear colour, black (RGBA format)

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the colour buffer (buffers enabled for colour writing) and depth buffer (buffer to visualise layering/ depth) --> creates uncoloured background layer
		
		glEnable(GL_SCISSOR_TEST); // Enable scissor test (discard pixels exceeding given dimensions from a given position)

		glScissor(m_viewportPositionX, m_viewportPositionY, m_viewportWidth, m_viewportHeight); // Set scissor test to the relative viewport, passing position and dimension parameters

		glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // Window clear colour, red (RGBA format)

		glClear(GL_COLOR_BUFFER_BIT); // Clear the colour buffer (buffers enabled for colour writing) --> creates coloured viewport

		glDisable(GL_SCISSOR_TEST); // Disable scissor test
		#pragma endregion
	}

	void GLFWWindowImpl::onResize(unsigned int width, unsigned int height) // Function, on resize window pass window dimensions (update values)
	{
		m_properties.m_width = width; // Set window width to the window propeties width
		m_properties.m_height = height; // Set window height to the window propeties height
	}

	void GLFWWindowImpl::setFullscreenMode(bool fullscreen) // Function, set window fullscreen mode passing fullscreen boolean 
	{
		m_properties.m_isFullScreen = fullscreen; // Set WindowProperties struct value 'm_isFullScreen' to the fullscreen variable being passed
		
		GLFWmonitor * monitor = glfwGetPrimaryMonitor(); // Create a GLFW monitor instance, set to the monitor used by the current computer system
		const GLFWvidmode * mode = glfwGetVideoMode(monitor); // Create a GLFW video mode instance, set to the mode of the monitor used by the current computer system

		if (fullscreen == true) // If the window is in fullscreen mode, do the following
		{
			int windowPositionX = 0; // Integer variable, store the current window position in the 'X' axis
			int windowPositionY = 0; // Integer variable, store the current window position in the 'Y' axis
			
			glfwGetWindowPos(m_nativeWindow, &windowPositionX, &windowPositionY); // Get the current window position in the 'X' and 'Y' axis, store positions in passed variables
			
			m_properties.m_windowedPositionX = windowPositionX; // Set 'm_windowPositionX' to the current window position in the 'X' axis
			m_properties.m_windowedPositionY = windowPositionY; // Set 'm_windowPositionY' to the current window position in the 'Y' axis

			m_properties.m_windowedWidth = m_properties.m_width; // Set 'm_windowedWidth' to the current window width dimension
			m_properties.m_windowedHeight = m_properties.m_height; // Set 'm_windowedHeight' to the current window height dimension

			// Set the window to the dimensions of the current monitor, and refresh rate of the monitor (enters fullscreen mode)
			glfwSetWindowMonitor(m_nativeWindow, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);

			ENGINE_TRACE("Window ENTERED fullscreen mode..."); // Output 'info' type to logger console window, identify the window as in fullscreen mode
		}
		else if (fullscreen == false) // Else if the window is not fullscreen mode, do the following
		{
			// Set the window to the default dimensions of the window, and refresh rate of the monitor, also set window position and dimensions to previously used windowed position and dimensions (becomes windowed)
			glfwSetWindowMonitor(m_nativeWindow, nullptr, m_properties.m_windowedPositionX, m_properties.m_windowedPositionY,
				m_properties.m_windowedWidth, m_properties.m_windowedHeight, mode->refreshRate); 

			ENGINE_TRACE("Window EXITED fullscreen mode..."); // Output 'info' type to logger console window, identify the window as in fullscreen mode
		}
	}

	void GLFWWindowImpl::setVSync(bool vSyncEnabled) // Function, set vSync activeness of a window
	{
		if (vSyncEnabled) // If vSync is enabled, do the following
		{
			glfwSwapInterval(1); // Swap front and back buffers of the window, for every screen update
		}
		else // If vSync is not enabled, do the following
		{
			glfwSwapInterval(0); // Swap the front and back buffers of the window without waiting for screen updates
		}

		m_properties.m_isVSync = vSyncEnabled; // Set vSync boolean variable, to passed parameter
	}
}