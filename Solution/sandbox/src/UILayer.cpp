/** \file UIlayer.cpp
*/

#include "engine_pch.h" // Include precompiled headers file

#include "../include/UILayer.h" // Include UILayer.h file

#include <glm/glm.hpp> // Include glm support

#include <glm/gtc/matrix_transform.hpp> // Include glm matrix transformation support

#include <ft2build.h> // Include Freetype build support //---> Not included in external dependacies for sandbox solution
#include FT_FREETYPE_H // Include Freetype support

	void UILayer::onAttach() // Intialise layer instance, on attach
	{
		m_pRenderer.reset(Engine::Renderer::createTextRenderer()); // Create text renderer instance

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////// Initialise freetype library /////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		FT_Library FreeType; // Freetype system
		FT_Face fontFace; // Freetype font face

		std::string fontFilepath("assets/fonts/TypoGraphica.otf"); // String storing filepath of font style

		int m_fontCharacterSize = 128; // Set font character glyph size

		if (FT_Init_FreeType(&FreeType)) // If FreeType system does not intialise, do the following
		{
			ENGINE_CRITICAL("Could not initialise FreeType!"); // Output 'critical' type to logger console window, output freetype initialisation error
		}

		if (FT_New_Face(FreeType, fontFilepath.c_str(), 0, &fontFace)) // load the font face for character glyphs
		{
			ENGINE_CRITICAL("Could not load font: {0}", fontFilepath); // Output 'critical' type to logger console window, output font loading failure
		}

		if (FT_Set_Pixel_Sizes(fontFace, 0, m_fontCharacterSize)) // Set the font size of character glyphs
		{
			ENGINE_CRITICAL("Could not set font face size of: {0}", m_fontCharacterSize); // Output 'critical' type to logger console window, output setting font face size error
		}

		if (FT_Load_Char(fontFace, 'G', FT_LOAD_RENDER)) // Load a character glyph, with its bound data
		{
			ENGINE_CRITICAL("Could not load the character glyph: {0}", 'G'); // Output 'critical' type to logger console window, output loading character glyph error
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////// Character render setup ////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_pGlyphTexture.reset(Engine::Texture::createFromRawData(
			fontFace->glyph->bitmap.width, // Width set
			fontFace->glyph->bitmap.rows, // Height set
			1, // Channels set
			fontFace->glyph->bitmap.buffer) // Data set
		); // Create a character glyph from raw data

		Engine::Character ch(
			glm::vec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows), // Size set
			glm::vec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top), // Bearing set
			fontFace->glyph->advance.x, // Advance set
			glm::vec2(0.0f), // Start UV coordinates set
			glm::vec2(1.0f) // End UV coordinates set
		); // Intialise character glyph parameters

		// Text vertices
		float textVertices[4 * 4] = {
			0,				0,				ch.getStartUV().x,	ch.getStartUV().y,
			ch.getSize().x, 0,				ch.getEndUV().x,	ch.getStartUV().y,
			ch.getSize().x, ch.getSize().y, ch.getEndUV().x,	ch.getEndUV().y,
			0,				ch.getSize().y, ch.getStartUV().x,	ch.getEndUV().y
		};

		// Text indices
		unsigned int textIndices[4] = { 0, 1, 2, 3 };

		m_pTextVAO = m_pResourceManager->addVAO("textCharacter"); // Create text vertex array object instance
		m_pTextShader = m_pResourceManager->addShader("assets/shaders/textCharacter.glsl"); // Create text shader object instance
		m_pTextVAO->setVertexBuffer(m_pResourceManager->addVBO("textCharacterVBO", textVertices, sizeof(textVertices), m_pTextShader->getBufferLayout())); // Create text vertex buffer object instance
		m_pTextVAO->setIndexBuffer(m_pResourceManager->addIndexBuffer("textCharacterIndices", textIndices, 4)); // Create text index buffer object instance

		m_pTextMaterial = m_pResourceManager->addMaterial("textCharacter", m_pTextShader, m_pTextVAO); // Create text material

		m_pCameraController.reset(new Engine::FreeOrthoCameraController2D()); // Create orthographic camera instance (UI)
		m_pCameraController->init(0.0f, 0.0f, 800.0f, 600.0f); // Initialise camera properties
	}

	void UILayer::onDetach() // Unset layer instance variables, on detach
	{
		m_pTextShader = nullptr; // Set m_pTextShader to point to NULL, at program termination
		m_pGlyphTexture = nullptr; // Set m_pGlyphTexture to point to NULL, at program termination
		m_pTextVAO = nullptr; // Set m_pTextVAO to point to NULL, at program termination
		m_pTextMaterial = nullptr; // Set m_pTextMaterial to point to NULL, at program termination

		m_pResourceManager = nullptr; // Set m_pResourceManager to point to NULL, at program termination
	}

	void UILayer::onUpdate(float timestep) // Update the UI layer instance, per passing frame
	{
		if (m_toggleCamera == true) // If 'm_toggleCamera' is 'true' (camera is active), do the following
		{
			m_pCameraController->onUpdate(timestep); // Update the orthographic camera, make controllable (camera controller active)
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////// Text renderer related code /////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_pRenderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(true)); // Set alpha blending to 'true' (enable)

		glm::mat4 m_textModel = glm::translate(glm::mat4(1.0f), glm::vec3(100, 200, 0)); // Set character glyph position translation
		glm::vec3 m_textColour(1.0f, 0.5f, 0.6f); // Set the character glyph colour

		unsigned int m_textSlot = m_pGlyphTexture->getSlot(); // Set the texture slot to the texture slot of the character glyph object instance

		std::map<std::string, void *> TextMap; // Create map to store text data, to be uploaded as a block

		TextMap.insert(std::make_pair("u_model", (void *)&m_textModel[0][0])); // Upload model data
		TextMap.insert(std::make_pair("u_view", (void *)&m_pCameraController->getCamera()->getView()[0][0])); // Upload view position data
		TextMap.insert(std::make_pair("u_projection", (void *)&m_pCameraController->getCamera()->getProjection()[0][0])); // Upload projection data
		TextMap.insert(std::make_pair("u_texData", (void *)&m_textSlot)); // Upload texture slot data
		TextMap.insert(std::make_pair("u_fontColour", (void *)&m_textColour[0])); // Upload colour data

		m_pTextMaterial->setDataBlock(TextMap); // Upload text data store in the map as a block of data

		m_pRenderer->submit(m_pTextMaterial); // Bind, upload and draw material (textured phong cube)

		m_pRenderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(false)); // Set alpha blending to 'false' (disable)
	}

	void UILayer::onEvent(Engine::Event & event) // Dispatch UI layer controlled events
	{
		m_pCameraController->onEvent(event); // Dispatch orthographic camera events
		
		Engine::EventDispatcher dispatcher(event); // Create an 'EventDispatcher' class object, passing an event type

		dispatcher.dispatch<Engine::KeyPressedEvent>(std::bind(&UILayer::onKeyPressedEvent, this, std::placeholders::_1)); // Dispatch key pressed event, binds and returns key pressed event, identifying handling state
	}

	bool UILayer::onKeyPressedEvent(Engine::KeyPressedEvent & event)
	{
		if (event.getKeyCode() == ENGINE_KEY_C) // If 'C' key is pressed, do the following...
		{
			m_toggleCamera = !m_toggleCamera; // Toggle the camera (toggle the updating camera each passing frame)

			if (m_toggleCamera == false) // If 'm_toggleCamera' is 'false' (perspective camera active), do the following
			{
				ENGINE_TRACE("Current camera: Perspective"); // Output 'trace' type to logger console window, output current camera in use is perspective
			}

			return false; // Return 'false', a key was not pressed and or held
		}
	}