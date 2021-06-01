/** \file application.h
*/

#pragma once // Compile once

#include "platform/windows/window.h" // Include window.h file

#include "systems/log.h" // Include system.h file

#include "systems/timer.h" // Include timer.h file

#include "systems/windows.h" // Include windows.h file

#include "core/keyCodes.h" // Include keyCodes.h file

#include "events/inputPoller.h" // Include inputPoller.h file

#include "assetmanager/resourceManager.h" // Include resourceManager.h file

#include "include/independent/core/layerstack.h" // Include layerstack.h file

namespace Engine //!< \namespace Engine namespace
{ 
	/**
	\class Application
	\brief Fundamental class of the engine. A singleton patterned class which runs 
	* the game loop infinitely. Provides the means of initialising instances of
	* windows and systems. Can also be used to create events and dispatch them.
	* Aswell, renderer index buffers and vertex buffers can be set, whilst vertex
	* arrays can be initialised. Shaders, textures and materials can be created
	* and applied to geometry. Also, multiple camera types can be created for
	* exploring a scene, or making alterations to the user interface.
	*/
	class Application
	{
	protected: // Protected members
		//! Constructor
		Application();

	private: // Private members
		static bool bRunning; //!< Boolean variable, loop program running (remains running until value becomes 'false')

		static Application* s_instance; //!< Singleton instance of the application

	public: // Public members
		std::shared_ptr<chronoTimer> m_pChronoTime; //!< Shared pointer, of type chronoTimer class (pointer to chronoTimer class)
		std::shared_ptr<MyLogger> m_pMyLogger; //!< Shared pointer, of type MyLogger class (pointer to MyLogger class)
		std::shared_ptr<WindowsSystem> m_pWindows; //!< Shared pointer, of type WindowsSystem class (pointer to WindowsSystem class)
		
		std::unique_ptr<Window> m_pWindow; //!< Unique pointer, of type Window class (pointer to Window class)

		std::shared_ptr<ResourceManager> m_pResourceManager; //!< Shared pointer, of type ResourceManager class (pointer to ResourceManager class)

		std::shared_ptr<Layerstack> m_pLayerstack; //!< Shared pointer, of type Layerstack class (pointer to Layerstack class) //***

		//! Takes reference to 'Window' class, instance getter
		/*!
		\return A dereferenced window class pointer (the window)
		*/
		inline Window& getWindow() { return *m_pWindow; }

		//!< Destructor
		virtual ~Application(); 
		
		//! Takes reference to application class, instance getter
		/*!
		\return A dereferenced application class pointer (the class object instance)
		*/
		inline static Application& getInstance() { return *s_instance; }

		void run(); //!< Main loop of the application

		//! Identifies and cast event types before dispatching them
		/*!
		\param e A reference to the Event class (base class of events)
		*/
		void onEvent(Event& e);

		//! Close window event
		/*!
		\param e A reference to the WindowCloseEvent class
		\return A boolean which identifies the event success
		*/
		bool onWindowClose(WindowCloseEvent& e);

		//! Resize window event
		/*!
		\param e A reference to the WindowResizeEvent class
		\return A boolean which identifies the event success
		*/
		bool onWindowResize(WindowResizeEvent& e);
		
		//! Focus window event
		/*!
		\param e A reference to the WindowFocusEvent class
		\return A boolean which identifies the event success
		*/
		bool onWindowFocus(WindowFocusEvent& e);

		//! Lost focus window event
		/*!
		\param e A reference to the WindowLostFocusEvent class
		\return A boolean which identifies the event success
		*/
		bool onWindowLostFocus(WindowLostFocusEvent& e);

		//! Moved window event
		/*!
		\param e A reference to the WindowMovedEvent class
		\return A boolean which identifies the event success
		*/
		bool onWindowMoved(WindowMovedEvent& e);

		//! Pressed key event
		/*!
		\param e A reference to the KeyPressedEvent class
		\return A boolean which identifies the event success
		*/
		bool onKeyPressedEvent(KeyPressedEvent& e);

	};
	//! To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}
