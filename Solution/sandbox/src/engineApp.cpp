/** \file engineApp.cpp
*/

#include "engineApp.h" // Include engineApp.h file

engineApp::engineApp() // Intialise game layers
{
	m_pLayerstack->push(std::make_shared<GameLayer>(GameLayer("Game Layer"))); // Push the game layer into the vector container (layerstack)
	m_pLayerstack->push(std::make_shared<UILayer>(UILayer("UI Layer"))); // Push the UI layer into the vector container (layerstack)
}

engineApp::~engineApp() // Destructor
{

}

Engine::Application * Engine::startApplication() // Start application
{
	return new engineApp(); // Return a new instance of the engineApp class
}