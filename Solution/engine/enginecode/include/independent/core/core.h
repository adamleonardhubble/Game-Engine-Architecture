/** \file core.h
*/

#pragma once // Compile once

#include "systems/log.h" // Include log.h file

//! Macro definition, assert criteria not matched (false)
#define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } } //!< \def Macro function definition, output assertion failure, call breakpoint at failure point