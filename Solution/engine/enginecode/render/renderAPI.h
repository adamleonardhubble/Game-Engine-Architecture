/** \file renderAPI.h
*/

#pragma once // Compile once

namespace Engine //!< \namespace Engine namespace
{
	/**
	\class RenderAPI
	\brief Interface class for all render API's. Provides means for initialisation 
	* and swapping graphics API at application runtime.
	*/
	class RenderAPI
	{
	public: // Public members
		/*!
		\class API
		\brief An enumerator type class, containing enumerators of render API's
		*/
		enum class API
		{
			None = 0, OpenGL = 1, Direct3D = 2 //!< Assign integer values (initialise) to each enumerator type, renderer specific 
		};

		//! Return the current renderer API
		/*!
		\return A enumerator type representing the current renderer API
		*/
		static API getAPI() { return m_API; }

	private: // Private members
		static API m_API; //!< Create enum class object, controls the render API in use
	};
}
