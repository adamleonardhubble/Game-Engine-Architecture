/** \file engineApp.h
*/

#pragma once // Compile once

#include <engine.h> // Include engine.h file

#include <memory> // Include memory support

#include "../independent/core/entrypoint.h" // Include entrypoint.h file

#include "../independent/core/layerstack.h" // Include layerstack.h file

#include "../include/gameLayer.h" // Include gameLayer.h file

#include "../include/UILayer.h" // Include UILayer.h file

/**
\class engineApp
\brief Fundamental class for engine applications. Provides 
* means for intialising engine applications and submitting
* application layers. Inherits from Application class.
*/
class engineApp : public Engine::Application
{
public: // Public members
	//! Constructor, intialise game layers
	engineApp();

	//! Destructor
	~engineApp() override;

};
