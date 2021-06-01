/** \file application.cpp
*/

#include "engine_pch.h" // Include precompiled headers file

#include "core/application.h" // Include application.h file

#ifdef NG_PLATFORM_WINDOWS // If windows platform is defined...
#include "platform/glfw/GLFWWindowsSystem.h" // Include GLFWWindowsSystem.h file
#endif // End if windows platform is defined...

bool Engine::Application::bRunning = true; // Intialise 'bRunning' to true (application is running at runtime entry)

namespace Engine // Engine namespace
{
	Application* Application::s_instance = nullptr; // Intialise 's_instance' to nullptr

	Application::Application() // Application constructor, find and or set application instance to pointer
	{
		if (s_instance == nullptr) // If 's_instance' is pointing to NULL, do the following
		{
			s_instance = this; // Set 's_instance' to point to an instance of the application class
		}

		m_pChronoTime = chronoTimer::getTimerInstance(); // Get instance of chronoTimer class, create one if none exist
		m_pMyLogger = MyLogger::getLoggerInstance(); // Get instance of MyLogger class, create one if none exist

		m_pChronoTime->start(SystemSignal::None); // Initiate (start) chrono during application execution
		m_pMyLogger->start(SystemSignal::None); // Initiate (start) logger during application execution

		#ifdef NG_PLATFORM_WINDOWS // If windows platform is defined...
		m_pWindows = GLFWWindowsSystem::getInstance(); // Get instance of GLFWWindowsSystem class, create one if none exist
		#endif // End if windows platform is defined...
		m_pWindows->start(SystemSignal::None); // Initiate (start) windows system during application execution

		m_pResourceManager.reset(new ResourceManager); // Create an instance of the resource manager class

		#ifdef NG_PLATFORM_WINDOWS // If windows platform is defined...
		m_pWindow = std::unique_ptr<Window>(Window::create()); // Create window instance, set with default window properties
		#endif // End if windows platform is defined...

		m_pWindow->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1)); // Set event callback, bind with Application::onEvent function
		
		m_pLayerstack.reset(new Layerstack()); // Create an instance of the layerstack class
	}

	Application::~Application() // Application destructor, destruct upon program termination 
	{
		m_pResourceManager->stop(SystemSignal::None); // Stop resource manager on program termination

		m_pChronoTime->stop(SystemSignal::None); // Stop chrono on program termination
		m_pMyLogger->stop(SystemSignal::None); // Stop logger on program termination
		m_pWindows->stop(SystemSignal::None); // Stop windows on program termination

		m_pLayerstack->stop(SystemSignal::None); // Stop layerstack on program termination
		
		m_pChronoTime = nullptr; // Set m_pChronoTime to point to NULL, at program termination
		m_pMyLogger = nullptr; // Set m_pMyLogger to point to NULL, at program termination
		m_pWindows = nullptr; // Set m_pWindows to point to NULL, at program termination

		m_pResourceManager = nullptr; // Set m_pResourceManager to point to NULL, at program termination

		m_pLayerstack = nullptr; // Set m_pLayerstack to point to NULL, at program termination
	}

	bool Application::onWindowClose(WindowCloseEvent& e) // Function, outputs runtime duration before application termination
	{
		ENGINE_WARN("Window is closing -------------------- Application runtime: {0} seconds", chronoTimer::m_runtimeDuration); // Output 'info' type to logger console window, output runtime duration and message of application termination
		bRunning = false; // Set 'bRunning' to false (application stop running)

		return true; // Return 'true', window has closed (application terminates)
	}

	bool Application::onWindowResize(WindowResizeEvent& e) // Function, outputs window resize dimensions
	{
		ENGINE_TRACE("Resize window. Width {0} Height {1}", e.getWidth(), e.getHeight()); // Output 'trace' type to logger console window, output window resize dimensions
		m_pWindow->onResize(e.getWidth(), e.getHeight()); // Update WindowProperties struct window dimensions, to the resized dimensions
		return true; // Return 'true', window has resized
	}

	bool Application::onWindowFocus(WindowFocusEvent& e) // Function, outputs window focus status
	{
		ENGINE_TRACE("Window IS focused..."); // Output 'trace' type to logger console window, output window focus status
		
		return true; // Return 'true', window is focused
	}

	bool Application::onWindowLostFocus(WindowLostFocusEvent& e) // Function, outputs window lost focus status
	{
		ENGINE_TRACE("Window LOST focus..."); // Output 'trace' type to logger console window, output window lost focus status
		
		return true; // Return 'true', window is not focused
	}

	bool Application::onWindowMoved(WindowMovedEvent& e) // Function, outputs window moved status
	{
		ENGINE_TRACE("Window moved: {0}, {1}", e.getWindowPositionX(), e.getWindowPositionY()); // Output 'trace' type to logger console window, output window moved status

		return true; // Return 'true', window has moved
	}

	bool Application::onKeyPressedEvent(KeyPressedEvent& e) // Function, outputs key pressed status
	{
		ENGINE_TRACE("Key pressed: {0}, Repeat count: {1}", (char)e.getKeyCode(), e.getKeyRepeatCount()); // Output 'trace' type to logger console window, output key code pressed and key repeat count

		if (e.getKeyCode() == ENGINE_KEY_ESCAPE) // If 'ESC' key is pressed, do the following...
		{
			ENGINE_TRACE("Window is closing -------------------- Application runtime: {0} seconds", chronoTimer::m_runtimeDuration); // Output 'trace' type to logger console window, output runtime duration and message of application termination
			bRunning = false; // Set 'bRunning' to false (application stop running)
		}
		if (e.getKeyCode() == ENGINE_KEY_SPACE) // If 'SPACE' key is pressed, do the following...
		{
			if (m_pWindow->isFullScreenMode() == true) // If the window is in fullscreen mode (true), do the following
			{
				m_pWindow->setFullscreenMode(false); // Set fullscreen mode to 'false', the window becomes windowed
			}
			else if (m_pWindow->isFullScreenMode() == false) // If the window is not in fullscreen mode (false), do the following
			{
				m_pWindow->setFullscreenMode(true); // Set fullscreen mode to 'true', the window becomes fullscreen
			}
		}
		if (e.getKeyCode() == ENGINE_KEY_ENTER) // If 'ENTER' key is pressed, do the following...
		{
			int mousePositionX = InputPoller::getMouseX(); // Set mousePositionX to the mouse position in 'X' axis
			int mousePositionY = InputPoller::getMouseY(); // Set mousePositionY to the mouse position in 'Y' axis

			ENGINE_TRACE("Mouse position: [{0}] [{1}]", mousePositionX, mousePositionY); // Output 'trace' type to logger console window, display 'X' and 'Y' mouse positions
		}

		return true; // Return 'true', a key was pressed and or held

	}

	void Application::onEvent(Event& e) // Function, identifies and casts event types before dispatching them
	{
		EventDispatcher dispatcher(e); // Create an 'EventDispatcher' class object, passing an event type

		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1)); // Dispatch windows close event, binds and returns window close event, identifying handling state
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onWindowResize, this, std::placeholders::_1)); // Dispatch windows resize event, binds and returns window resize event, identifying handling state

		dispatcher.dispatch<WindowFocusEvent>(std::bind(&Application::onWindowFocus, this, std::placeholders::_1)); // Dispatch windows focus event, binds and returns window focus event, identifying handling state
		dispatcher.dispatch<WindowLostFocusEvent>(std::bind(&Application::onWindowLostFocus, this, std::placeholders::_1)); // Dispatch windows lost focus event, binds and returns window lost focus event, identifying handling state

		dispatcher.dispatch<WindowMovedEvent>(std::bind(&Application::onWindowMoved, this, std::placeholders::_1)); // Dispatch windows moved event, binds and returns window moved event, identifying handling state
	
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Application::onKeyPressedEvent, this, std::placeholders::_1)); // Dispatch key pressed event, binds and returns key pressed event, identifying handling state
	
		for (auto it = m_pLayerstack->end(); it != m_pLayerstack->begin(); ) // For all layers in the layerstack, do the following (from end to start)
		{
			(*--it)->onEvent(e); // Dispatch the events inversed (front to back)

			if (e.bEventHandled() == true) // If the event being dispatched has been handled (true), do the following
			{
				break; // Break from the loop
			}
		}
	}

	void Application::run() // Function, application run (main loop)
	{
		while (bRunning) // While bRunning is true, do the following
		{
			CHRONO_FRAMERATE; // Macro function, calculate FPS from each application loop iteration

			CHRONO_RUNTIME; // Macro function, calculate application runtime duration

			float timePassed = CHRONO_TIMEPASSED; // Set 'timePassed' to the timestep (time between passing frames)

			for (auto it = m_pLayerstack->begin(); it != m_pLayerstack->end(); it++) // For all layers in the layerstack, do the following (start to end)
			{
				(*it)->onUpdate(chronoTimer::m_frameSecondsPassed); // Update each layer in the layerstack, per passing frame
			}

			m_pWindow->onUpdate(chronoTimer::m_frameSecondsPassed); // Update application window, per passing frame

			//CHRONO_CLOCK_START; // Macro function, start time point (start measuring time passed now)
			//CHRONO_CLOCK_STOP; // Macro function, stop time point (stop measuring time passed and calculate it)
		}
		
		// Macro functions only called when 'bRunning' is false (stop running application)
		ENGINE_INFO("Status of chrono time system: {0}", bRunning); // Output 'info' type to logger console window, return running status of logger
		ENGINE_INFO("Status of logging system: {0}", m_pMyLogger->bRunning()); // Output 'info' type to logger console window, return running status of logger
	}
}
