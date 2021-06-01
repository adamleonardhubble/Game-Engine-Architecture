/** \file engine.h
* A header file which includes relevant headers for development
*/

#pragma once // Compile once

// Entry point
//#include "include/independent/core/entrypoint.h"

//----------------------------------------- Input -----------------------------------------------//
#include "core/keyCodes.h" // Include keyCodes.h file
#include "events/inputPoller.h" // Include inputPoller.h file

//---------------------------------------- Rendering --------------------------------------------//
#include "render/material.h" // Include material.h file
#include "render/renderer/renderer.h" // Include renderer.h file
#include "render/text/character.h" // Include character.h file

//----------------------------------------- Camera ----------------------------------------------//
#include "render/camera/cameraController.h" // Include cameraController.h file
#include "render/camera/FPSCameraControllerEuler.h" // Include FPSCameraControllerEuler.h file
#include "render/camera/freeOrthoCameraController2D.h" // Include freeOrthoCameraController2D.h file
