/** \file gameLayer.cpp
*/

#include "engine_pch.h" // Include precompiled headers file

#include "../include/gameLayer.h" // Include gameLayer.h file

#include <glm/glm.hpp> // Include glm support

#include <glm/gtc/matrix_transform.hpp> // Include glm matrix transformation support

	void GameLayer::onAttach() // Intialise the game layer instance, on attach
	{
		m_pRenderer.reset(Engine::Renderer::createBasic3D()); // Create renderer instance (simple renderer)

		m_pRenderer->actionCommand(Engine::RenderCommand::setDepthTestLessCommand(true)); // Set depth test less to 'true' (enable)
		m_pRenderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(true)); // Set backface culling to 'true' (enable)

		// Cube vertices (used for both cubes)
		unsigned int indices[3 * 12] = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
		};

		// Full colour cube vertices
		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // Red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // Green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // Magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // Yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		m_pFCVAO = m_pResourceManager->addVAO("flatColourCube"); // Create full colour cube vertex array object instance
		m_pFCShader = m_pResourceManager->addShader("assets/shaders/flatColour.glsl"); // Create full colour cube shader object instance
		m_pFCVAO->setVertexBuffer(m_pResourceManager->addVBO("FlatColourVBO", FCvertices, sizeof(FCvertices), m_pFCShader->getBufferLayout())); // Create full colour cube vertex buffer object instance
		m_pFCVAO->setIndexBuffer(m_pResourceManager->addIndexBuffer("FlatCubeIndices", indices, 3 * 12)); // Create full colour cube index buffer object instance

		m_pFCMaterial = m_pResourceManager->addMaterial("flatColourCube", m_pFCShader, m_pFCVAO); // Create textured phong cube material

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////// Textured phong shader and cube //////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Textured phong cube vertices
		float TPvertices[8 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
			 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
			-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
			-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
			 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
			-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
			-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
			 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
			 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
			-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
			-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
			 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
			 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
			-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
			-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
			-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
			0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
			0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		};

		m_pTPVAO = m_pResourceManager->addVAO("texturedPhongCube"); // Create textured phong cube vertex array object instance
		m_pTPShader = m_pResourceManager->addShader("assets/shaders/texturedPhong.glsl"); // Create textured phong cube shader object instance
		m_pTPVAO->setVertexBuffer(m_pResourceManager->addVBO("texturedPhongVBO", TPvertices, sizeof(TPvertices), m_pTPShader->getBufferLayout())); // Create textured phong cube vertex buffer object instance
		m_pTPVAO->setIndexBuffer(m_pResourceManager->addIndexBuffer("TexturedCubeIndices", indices, 3 * 12)); // Create textured phong cube index buffer object instance

		m_pTPMaterial = m_pResourceManager->addMaterial("texturedPhongCube", m_pTPShader, m_pTPVAO); // Create textured phong cube material

		m_pLetterTexture = m_pResourceManager->addTexture("assets/textures/letterCube.png"); // Create textured phong cube texture object instance (letters)
		m_pNumberTexture = m_pResourceManager->addTexture("assets/textures/numberCube.png"); // Create textured phong cube texture object instance (numbers)

		m_FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3)); // Set the intial position translation of the flat colour cube
		m_TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3)); // Set the intial position translation of the textured phong cube

		m_pMatricesUBO = m_pResourceManager->getUBO("Matrices"); // Set 'm_pMatricesUBO' to the the uniform buffer object pointer 'Matrices'
		m_pLightsUBO = m_pResourceManager->getUBO("Lights"); // Set 'm_pLightsUBO' to the the uniform buffer object pointer 'Lights'

		m_pCameraController.reset(new Engine::FPSCameraControllerEuler()); // Create perspective camera instance (First-person)
		m_pCameraController->init(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); // Initialise camera properties
	}

	void GameLayer::onDetach() // Unset the game layer instance variables, on detach
	{
		m_pFCShader = nullptr; // Set m_pFCShader to point to NULL, at program termination
		m_pTPShader = nullptr; // Set m_pTPShader to point to NULL, at program termination

		m_pLetterTexture = nullptr; // Set m_pLetterTexture to point to NULL, at program termination
		m_pNumberTexture = nullptr; // Set m_pNumberTexture to point to NULL, at program termination

		m_pFCVAO = nullptr; // Set m_pFCVAO to point to NULL, at program termination
		m_pTPVAO = nullptr; // Set m_pTPVAO to point to NULL, at program termination

		m_pFCMaterial = nullptr; // Set m_pFCMaterial to point to NULL, at program termination
		m_pTPMaterial = nullptr; // Set m_pTPMaterial to point to NULL, at program termination

		m_pMatricesUBO = nullptr; // Set m_pMatricesUBO to point to NULL, at program termination
		m_pLightsUBO = nullptr; // Set m_pLightsUBO to point to NULL, at program termination

		m_pResourceManager = nullptr; // Set m_pResourceManager to point to NULL, at program termination
	}

	void GameLayer::onUpdate(float timestep) // Update the game layer instance, per passing frame
	{
		if (m_toggleCamera == true) // If 'm_toggleCamera' is 'true' (camera is active), do the following
		{
			m_pCameraController->onUpdate(timestep); // Update the perspective camera, make controllable (camera controller active)
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////// Geometry renderer related code ////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_pRenderer->actionCommand(Engine::RenderCommand::setClearColourCommand(0.8, 0.8, 0.8, 1.0)); // Set window clear colour (currently grey)
		m_pRenderer->actionCommand(Engine::RenderCommand::clearDepthColourBufferCommand()); // Clear window depth colour buffer
		m_pRenderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(true)); // Set backface culling to 'true' (enable)

		glm::mat4 FCtranslation, TPtranslation; // Translation matrices (cubes)

		if (m_goingUp) // If 'm_goingUp' is 'true', do the following
		{
			FCtranslation = glm::translate(m_FCmodel, glm::vec3(0.0f, 0.2f * timestep, 0.0f)); // Flat colour cube position, translates upwards in 'Y' axis
			TPtranslation = glm::translate(m_TPmodel, glm::vec3(0.0f, -0.2f * timestep, 0.0f)); // Textured phong cube position, translates downwards in 'Y' axis
		}
		else // Else if 'm_goingUp' is 'false', do the following
		{
			FCtranslation = glm::translate(m_FCmodel, glm::vec3(0.0f, -0.2f * timestep, 0.0f)); // Flat colour cube position, translates downwards in 'Y' axis
			TPtranslation = glm::translate(m_TPmodel, glm::vec3(0.0f, 0.2f * timestep, 0.0f)); // Textured phong cube position, translates upwards in 'Y' axis
		}

		m_timeSummed += timestep; // Increment the time elapsed by continually adding the time between each passing frame 
		if (m_timeSummed > 20.0f) // If the time elapsed is '20.0' seconds or more, do the following
		{
			m_timeSummed = 0.f; // Set the time elapsed to '0' (reset timer)
			m_goingUp = !m_goingUp; // Toggle the translation of the cubes, inverse their translation in the 'Y' axis 
		}

		m_FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at '20' degrees per second, positively
		m_TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at '20' degrees per second, negatively

		m_lightPosition = glm::vec4(0.0f, 3.0f, -6.0f, 1.0f); // Set light position uniform variable values
		m_viewPosition = glm::vec4(0.0f, 0.0f, -4.5f, 1.0f); // Set view position uniform variable values
		m_lightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Set light colour uniform variable values

		std::vector<void * > matricesContainer; // Create vector container of void pointers, used to store 'matrice' uniform variables
		matricesContainer.push_back((void *)&m_pCameraController->getCamera()->getProjection()[0][0]); // Add the geometry projection uniform variable to the vector container
		matricesContainer.push_back((void *)&m_pCameraController->getCamera()->getView()[0][0]); // Add the geometry view uniform variable to the vector container

		sceneData.insert(std::make_pair(m_pMatricesUBO, matricesContainer)); // Insert the matrices UBO instance pointer and the matrice uniform variable container, into the 'sceneData' class map

		std::vector<void *> lightsContainer; // Create vector container of void pointers, used to store 'light' uniform variables
		lightsContainer.push_back((void *)&m_lightColour[0]); // Add the light colour uniform variable to the vector container
		lightsContainer.push_back((void *)&m_lightPosition[0]); // Add the light position uniform variable to the vector container
		lightsContainer.push_back((void *)&m_viewPosition[0]); // Add the view position uniform variable to the vector container

		sceneData.insert(std::make_pair(m_pLightsUBO, lightsContainer)); // Insert the lights UBO instance pointer and the light uniform variable container, into the 'sceneData' class map

		m_pRenderer->beginScene(sceneData); // Prepare the scene data map for submission, create a uniform buffer layout from each element in the map

		m_pFCMaterial->setDataElement("u_model", (void *)&m_FCmodel[0][0]); // Upload model data

		m_pRenderer->submit(m_pFCMaterial); // Bind, upload and draw material (full colour cube)

		if (m_goingUp) // If 'm_goingUp' is 'true', do the following
		{
			m_texSlot = m_pLetterTexture->getSlot(); // Return the texture slot of the textured phong cube (letters)
		}
		else // If 'm_goingUp' is 'false' (going down), do the following
		{
			m_texSlot = m_pNumberTexture->getSlot(); // Return the texture slot of the textured phong cube (numbers)
		}

		std::map<std::string, void *> TPuniformMap; // Create map to store uniform data, to be uploaded as a block

		//m_pTPShader->setDataElement("u_objectColour", (void*)&tpMVP[0][0]); // Upload object colour data

		TPuniformMap.insert(std::make_pair("u_model", (void *)&m_TPmodel[0][0])); // Upload model data
		TPuniformMap.insert(std::make_pair("u_texData", (void *)&m_texSlot)); // Upload texture slot data

		m_pTPMaterial->setDataBlock(TPuniformMap); // Upload uniform data store in the map as a block of data

		m_pRenderer->submit(m_pTPMaterial); // Bind, upload and draw material (textured phong cube)

		m_pRenderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(false)); // Set backface culling to 'false' (disable)

		for (auto& CGO : m_gameObjects) // For all game object components, do the following
		{
			CGO->onUpdate(timestep); // Update game object components, per passing frame
		}
	}

	void GameLayer::onEvent(Engine::Event & event) // Dispatch game layer controlled events
	{
		m_pCameraController->onEvent(event); // Dispatch perspective camera events

		for (auto& CGO : m_gameObjects) // For all game object components, do the following
		{
			CGO->onEvent(event); // Dispatch game object component events
		}

		Engine::EventDispatcher dispatcher(event); // Create an 'EventDispatcher' class object, passing an event type

		dispatcher.dispatch<Engine::KeyPressedEvent>(std::bind(&GameLayer::onKeyPressedEvent, this, std::placeholders::_1)); // Dispatch key pressed event, binds and returns key pressed event, identifying handling state
	}

	bool GameLayer::onKeyPressedEvent(Engine::KeyPressedEvent & event) // Function, outputs key pressed status
	{
		if (event.getKeyCode() == ENGINE_KEY_C) // If 'C' key is pressed, do the following...
		{
			m_toggleCamera = !m_toggleCamera; // Toggle the camera (toggle the updating camera each passing frame)

			if (m_toggleCamera == false) // If 'm_toggleCamera' is 'false' (orthographic camera active), do the following
			{
				ENGINE_TRACE("Current camera: Orthographic"); // Output 'trace' type to logger console window, output current camera in use is orthographic
			}

			return true; // Return 'true', a key was pressed and or held
		}
	}
