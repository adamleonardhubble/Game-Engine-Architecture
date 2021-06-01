/** \file layerstack.h
*/

#pragma once // Compile once

#include "systems/system.h" // Include system.h file

#include "include/independent/core/layer.h" // Include layer.h file

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class Layerstack
	\brief Class for handling all layer type instances. Provides means 
	* for initialisation and creation of layers, adding layers to the
	* layerstack and iterating through the layers stored in the layerstack.
	*/
	class Layerstack : public Engine::System
	{
	private: // Private members
		std::vector<std::shared_ptr<Layer>> m_layers; //!< Vector container, store shared pointer instances to the Layer class

	public: // Public members
		//! Default constructor
		Layerstack() {};

		//! Default destructor
		~Layerstack() {};

		void start(SystemSignal init = SystemSignal::None, ...) {}; //!< Override function, start layerstack system

		void stop(SystemSignal close, ...); //!< Override function, stop layerstack system

		void push(std::shared_ptr<Layer> layer) { m_layers.push_back(layer); init(layer); } //!< Push a layer instance into the vector container

		void init(std::shared_ptr<Layer> layer); //!< Initialise each layer instance

		void pop(); //!< Pop a layer instance off the vector container

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_layers.begin(); } //!< Return the layer instance at the start of the vector container

		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_layers.end(); } //!< Return the layer instance at the end of the vector container

	};
}