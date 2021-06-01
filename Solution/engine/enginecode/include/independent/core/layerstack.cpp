/** \file layerstack.cpp
*/

#include "engine_pch.h" // Include precompiled headers file

#include "layerstack.h" // Include layerstack.h file

namespace Engine // Engine namespace
{
	void Layerstack::stop(SystemSignal close, ...) // Stop the layerstack system
	{
		for (std::shared_ptr<Layer> layer : m_layers) // For each instance of layer class pointer contained within the vector container, do the following
		{
			layer->onDetach(); // Call each layers 'onDetach' method
			layer = nullptr; // Set the current layer pointer to point to NULL, at program termination
		}
	}

	void Layerstack::init(std::shared_ptr<Layer> layer) // Initialise each layer instance
	{
		layer->onAttach(); // Call each passed layers 'onAttach' method

		ENGINE_TRACE("Layer intialised: [{0}]", layer->getName()); // Output 'trace' type to logger console window, display name of the initialised layer
	}

	void Layerstack::pop() // Pop a layer instance off the vector container
	{
		
	}
}
