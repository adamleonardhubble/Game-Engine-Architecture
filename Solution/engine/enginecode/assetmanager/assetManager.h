/** \file assetManager.h
*/

#pragma once // Compile once

#include <map> // Include map support

#include <string> // Include string support

#include "systems/log.h" // Include log.h file

/**
\class AssetManager
\brief A templated class <G> which stores a parameterised type in a
* map. Makes use of shared pointers to add each assets components
* into the map.
*/
template <class G>
class AssetManager
{
private: // Private members
	std::map<std::string, std::shared_ptr<G>> m_container; //!< Map, store the assets in one container (asset name, pointer to asset object instance)

public: // Public members
	bool contains(const std::string& name); //!< Function, check whether a asset or item is already within the map

	//! Add a new asset to the map (container)
	/*!
	\param name A reference to a string representing the name of the asset being added
	\param element A reference to a shared pointer type representing the pointer to the asset and its class being added
	*/
	void add(const std::string& name, std::shared_ptr<G>& element);

	//! Retrieve a pointer to the asset and its class (return 'nullptr' if non-existent)
	/*!
	\param name A reference to a string representing the name of the asset to be retrieved from the map
	\return A shared pointer type to the corresponding asset and its class in the map
	*/
	std::shared_ptr<G> get(const std::string& name);

	void emptyContainer(); //!< Empty the map, removing and destroying all the assets, the size of the map becomes '0'

};

template<class G>
inline bool AssetManager<G>::contains(const std::string & name) // Check whether a asset or item is already within the map
{
	if (m_container.find(name) != m_container.end()) // If an asset pointer name matches the passed pointer name and is not at the end of the map, do the following
	{
		return true; // Return 'true' (pointer by such name exists and was found in the map)
	}
	else // Else if the passed pointer name has no matching pointer name, do the following
	{
		return false; // Return 'false' (pointer by such name does not exist in the map)
	}
}

template<class G>
inline void AssetManager<G>::add(const std::string & name, std::shared_ptr<G>& element) // Add a pair to the asset manager map, based on the passed parameters
{
	std::pair<std::string, std::shared_ptr<G>> AddElementPair; // Create a pair, macthing the asset manager map components

	AddElementPair.first = name; // Set the pairs first component (string), to the passed name of the asset being added
	AddElementPair.second = element; // Set the pairs second component (pointer), to the passed pointer of the asset being added (pointer to class of asset type)

	if (contains(name) == true) // If the passed asset name already exists in the asset manager map, do the following
	{
		ENGINE_CRITICAL("An asset by the name of '{0}' already exists!", name); // Output type 'critical' to the logger console output window, output an asset of such name already exists
	}
	else // Else if the passed asset name does not exist in the asset manager map, do the following
	{
		m_container.insert(AddElementPair); // Add the pair to the asset manager map, a new asset is stored
	}
}

template<class G>
inline std::shared_ptr<G> AssetManager<G>::get(const std::string & name) // Return a pointer to the passed asset name (if existing)
{
	std::map<std::string, std::shared_ptr<G>>::iterator it; // Create a map iterator, matching the asset manager map components

	it = m_container.find(name); // Set the map iterator to the asset manager map, in search for the passed asset name

	if (contains(name) == true) // If the name of the asset passed, exists as an asset in the asset manager map, do the following
	{
		return it->second; // Return the asset pointer (stored in the second component in the map)
	}
	else // If the name of the asset passed, does not exist in the asset manager map, do the following
	{
		ENGINE_CRITICAL("No asset of the name '{0}' could be located!", name); // Output type 'critical' to the logger console output window, output the asset of such name could not be located
	}
}

template<class G>
inline void AssetManager<G>::emptyContainer() // Empty the map, removing and destroying all the assets, the size of the map becomes '0'
{
	m_container.clear(); // Empty the map (remove and destroy all assets)

	ENGINE_CRITICAL("Container is empty: {0}", m_container.empty()); // Output type 'critical' to the logger console output window, output whether the asset map is empty or not empty
}
