/** \file renderAPI.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "render/renderAPI.h" // Include renderAPI.h file

namespace Engine // Engine namespace
{
	RenderAPI::API RenderAPI::m_API = RenderAPI::API::OpenGL; // Set (intialise) the render API to 'OpenGL'
}