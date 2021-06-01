/** \file graphicsContext.h
*/

#pragma once // Compile once

/**
\class GraphicsContext 
\brief A class serving as an interface class, for all graphics contexts.
* Provides means for graphics rendering initialisation and swapchain 
* implementation.
*/
class GraphicsContext
{
public: // Public members
	virtual void init() = 0; //!< Intialise graphics rendering

	virtual void swapBuffers() = 0; //!< Intialise buffering system (swapchain)
};