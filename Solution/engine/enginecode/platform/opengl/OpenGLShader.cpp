/** \file OpenGLShader.cpp
*/

#include "engine_pch.h" // Include precompiled headers

#include "platform/opengl/OpenGLShader.h" // Include OpenGLShader.h file

#include "core/core.h" // Include core.h file

#include <fstream> // Include fstream support

#include <sstream> // Include stringstream support

namespace Engine // Engine namespace
{
	static ShaderDataType GLSLStrToSDT(const std::string& glslSrc) // Convert a string to its corresponding shader data type
	{
		ShaderDataType result = ShaderDataType::None; // If the result is 'nothing', the data type is 'none'
		if (glslSrc == "int") result = ShaderDataType::Int; // If the result is 'int', the data type is 'int'
		if (glslSrc == "ivec2") result = ShaderDataType::Int2; // If the result is 'vec2', the data type is 'int2'
		if (glslSrc == "ivec3") result = ShaderDataType::Int3; // If the result is 'vec3', the data type is 'int3'
		if (glslSrc == "ivec4") result = ShaderDataType::Int4; // If the result is 'vec4', the data type is 'int4'
		if (glslSrc == "float") result = ShaderDataType::Float; // If the result is 'float', the data type is 'float'
		if (glslSrc == "vec2") result = ShaderDataType::Float2; // If the result is 'vec2', the data type is 'float2'
		if (glslSrc == "vec3") result = ShaderDataType::Float3; // If the result is 'vec3', the data type is 'float3'
		if (glslSrc == "vec4") result = ShaderDataType::Float4; // If the result is 'vec4', the data type is 'float4'
		if (glslSrc == "mat3") result = ShaderDataType::Mat3; // If the result is 'mat3', the data type is 'mat3'
		if (glslSrc == "mat4") result = ShaderDataType::Mat4; // If the result is 'mat4', the data type is 'mat4'
		if (glslSrc == "bool") result = ShaderDataType::Bool; // If the result is 'bool', the data type is 'bool'
		if (glslSrc == "sampler2D") result = ShaderDataType::Sampler2D; // If the result is 'sampler2D', the data type is 'sampler2D'

		return result; // Return '0' (nothing)
	}

	OpenGLShader::OpenGLShader(const std::string & filepath) // Create, compile and link shader from a single filepath source
	{
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a vertex shader object

		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader object

		parseSource(filepath); // Parse the source code from a single source (extrapolate its components)

		UniformLayout::iterator UniformLayoutMapInterator; // Uniform layout map iterator instance

		for (const auto& UniformLayoutMapInterator : m_UniformLayout) // For all the uniform layout map components, do the following
		{
			const std::string UniformName = UniformLayoutMapInterator.first; // Create and set 'UniformName' string to the uniform layout map component one (the name of the uniform)

			GLuint UniformLocation = glGetUniformLocation(m_OpenGL_ID, UniformName.c_str()); // Get the location of the current uniform variable, store as a GL unsigned integer

			m_UniformLayout.find(UniformName)->second.second = (int)UniformLocation; // Set the location of the uniform variable in the second component of the map, in the second component of the pair in the map (casted to an integer)
		}
	}

	OpenGLShader::OpenGLShader(const std::string & vertexFilepath, const std::string & fragmentFilepath) // Create, compile and link shader from multiple filepath sources
	{
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a vertex shader object

		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader object

		parseSource(vertexFilepath, fragmentFilepath); // Parse the source code from multiple sources (extrapolate its components)

		UniformLayout::iterator UniformLayoutMapInterator; // Uniform layout map iterator instance

		for (const auto& UniformLayoutMapInterator : m_UniformLayout) // For all the uniform layout map components, do the following
		{
			const std::string UniformName = UniformLayoutMapInterator.first; // Create and set 'UniformName' string to the uniform layout map component one (the name of the uniform)

			GLuint UniformLocation = glGetUniformLocation(m_OpenGL_ID, UniformName.c_str()); // Get the location of the current uniform variable, store as a GL unsigned integer

			m_UniformLayout.find(UniformName)->second.second = (int)UniformLocation; // Set the location of the uniform variable in the second component of the map, in the second component of the pair in the map (casted to an integer)
		}
	}

	OpenGLShader::~OpenGLShader() // Destructor
	{
		glDeleteProgram(m_OpenGL_ID); // Delete the rendering program m_OpenGL_ID
	}

	void OpenGLShader::Bind() const // Bind the shader object
	{
		glUseProgram(m_OpenGL_ID); // Use m_OpenGL_ID as a rendering program
	}

	void OpenGLShader::Unbind() const // Unbind the shader object
	{
		glUseProgram(0); // Do not use a object as a rendering program
	}

	bool OpenGLShader::uploadData(const std::string & name, void * data) // Upload data of any type to the GPU
	{
		std::pair<ShaderDataType, int> UniformDataTypeAndLocation; // Create pair, used to store uniform data type and location
		
		UniformLayout::iterator UniformLayoutMapInterator; // Uniform layout map iterator instance

		UniformLayoutMapInterator = m_UniformLayout.find(name); // Set the uniform layout map iterator to iterate and find the passed uniform variable name, in the uniform layout map

		if (UniformLayoutMapInterator == m_UniformLayout.end()) // If the map iterator reaches the end of the uniform layout map, do the following (no uniform variable found)
		{
			ENGINE_CRITICAL("No uniform variable of the name '{0}' could be located!", name); // Output type 'crtical' to the logger console window, output a uniform variable could not be found
		}
		else // Else if the map iterator reaches a uniform variable name in uniform layout map that matches the passed name, do the following
		{
			UniformDataTypeAndLocation.second = (int)UniformLayoutMapInterator->second.second; // Set 'location' to the map 'location'
			UniformDataTypeAndLocation.first = UniformLayoutMapInterator->second.first; // Set 'name' to the map 'ShaderDataType'
		}

		GLuint UniformLocation = UniformDataTypeAndLocation.second; // Set and store the location component in the pair to 'UniformLocation'

		dispatchUniformData(UniformDataTypeAndLocation.first, UniformLocation, data); // Dispatch the uniform variable data (create uniform variable instances based on data type passed)

		return true; // Return 'true' (dispatch successful)
	}

	bool OpenGLShader::uploadData(const UniformLayout & uniforms) // Upload data of any type to the GPU
	{
		m_UniformLayout = uniforms; // Set the uniform layout of the shader data

		return true;  // Return 'true' (dispatch successful)
	}

	void OpenGLShader::dispatchUniformData(ShaderDataType dataType, GLuint uniformLocation, void * uniformData) // Dispatch shader uniform variable data
	{
		const float * valueFloatMulti; // Float pointer, store the uniform variable data of multi dimension float data types (float vectors)
		const int * valueIntegerMulti; // Integer pointer, store the uniform variable data of multi dimension integer data types (integer vectors)

		GLfloat valueFloat; // GL float, store the uniform variable data for float data types
		GLint valueInteger; // GL integer, store the uniform variable data for integer data types

		switch (dataType) // Switch case statement, dependant on the passed uniform variable data type
		{
		case ShaderDataType::Sampler2D: // If the data type is a sampler2D type, do the following
			valueInteger = *(int*)uniformData; // Set 'valueInteger' to the uniform variable data (casted to a integer type and dereferenced)
			glUniform1i(uniformLocation, valueInteger); // Create a uniform variable of type integer, set the location of the variable to its passed address and casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Bool: // If the data type is a boolean type, do the following
			valueInteger = *(bool*)uniformData; // Set 'valueInteger' to the uniform variable data (casted to a boolean type and dereferenced)
			glUniform1i(uniformLocation, valueInteger);  // Create a uniform variable of type integer, set the location of the variable to its passed address and casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Int: // If the data type is a integer type, do the following
			valueInteger = *(int*)uniformData; // Set 'valueInteger' to the uniform variable data (casted to a integer type and dereferenced)
			glUniform1i(uniformLocation, valueInteger);  // Create a uniform variable of type integer, set the location of the variable to its passed address and casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Int2: // If the data type is a integer2 type, do the following
			valueIntegerMulti = (const int*)uniformData; // Set 'valueIntegerMulti' to the uniform variable data (casted to a integer pointer type)
			glUniform2iv(uniformLocation, 1, valueIntegerMulti); // Create a uniform variable of type integer, set the location of the variable to its passed address, set its size (count) and its casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Int3: // If the data type is a integer3 type, do the following
			valueIntegerMulti = (const int*)uniformData; // Set 'valueIntegerMulti' to the uniform variable data (casted to a integer pointer type)
			glUniform3iv(uniformLocation, 1, valueIntegerMulti); // Create a uniform variable of type integer, set the location of the variable to its passed address, set its size (count) and its casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Int4: // If the data type is a integer4 Sampler2D type, do the following
			valueIntegerMulti = (const int*)uniformData; // Set 'valueIntegerMulti' to the uniform variable data (casted to a integer pointer type)
			glUniform4iv(uniformLocation, 1, valueIntegerMulti); // Create a uniform variable of type integer, set the location of the variable to its passed address, set its size (count) and its casted data)
			break; // Break from the switch case statement
			
		case ShaderDataType::Float: // If the data type is a float type, do the following
			valueFloat = *(float*)uniformData; // Set 'valueFloat' to the uniform variable data (casted to a float type and dereferenced)
			glUniform1f(uniformLocation, valueFloat); // Create a uniform variable of type float, set the location of the variable to its passed address and casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Float2: // If the data type is a float2 type, do the following
			valueFloatMulti = (const float*)uniformData; // Set 'valueFloatMulti' to the uniform variable data (casted to a float pointer type)
			glUniform2fv(uniformLocation, 1, valueFloatMulti); // Create a uniform variable of type float, set the location of the variable to its passed address, set its size (count) and its casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Float3: // If the data type is a float3 type, do the following
			valueFloatMulti = (const float*)uniformData; // Set 'valueFloatMulti' to the uniform variable data (casted to a float pointer type)
			glUniform3fv(uniformLocation, 1, valueFloatMulti); // Create a uniform variable of type float, set the location of the variable to its passed address, set its size (count) and its casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Float4: // If the data type is a float4 type, do the following
			valueFloatMulti = (const float*)uniformData; // Set 'valueFloatMulti' to the uniform variable data (casted to a float pointer type)
			glUniform4fv(uniformLocation, 1, valueFloatMulti); // Create a uniform variable of type float, set the location of the variable to its passed address, set its size (count) and its casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Mat3: // If the data type is a matrix3 type, do the following
			valueFloatMulti = (const float*)uniformData; // Set 'valueFloatMulti' to the uniform variable data (casted to a float pointer type)
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, valueFloatMulti); // Create a uniform variable of type float, set the location of the variable to its passed address, set its size (count), set the column and row formation of the matrix to stay the same (false) and set its casted data)
			break; // Break from the switch case statement

		case ShaderDataType::Mat4: // If the data type is a matrix4 type, do the following
			valueFloatMulti = (const float*)uniformData; // Set 'valueFloatMulti' to the uniform variable data (casted to a float pointer type)
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, valueFloatMulti); // Create a uniform variable of type float, set the location of the variable to its passed address, set its size (count), set the column and row formation of the matrix to stay the same (false) and set its casted data)
			break; // Break from the switch case statement
		}
	}

	void OpenGLShader::extractUniformLayout(const std::string& line, bool uniformBlock) // Extract the uniform layout (per-line)
	{
		std::string uniformVariableDataType; // String, store the uniform variable shader data type
		std::string uniformVariableName; // String, store the uniform variable name

		std::stringstream uniformLayout(line); // Stringstream instance, store and stream every passed line of uniform variable source code

		bool bFoundUniform = false; // Boolean variable, identify whether a uniform variable declaration has been found or not found

		while (uniformLayout >> uniformVariableDataType) // While the source code is being streamed to the 'uniformVariableDataType' string, do the following
		{
			if (bFoundShaderUniformBlock == false) // If a shader uniform block has not been found, do the following
			{
				if (uniformBlock == true) // If the extracted line of source code contains a shader uniform block declaration, do the following
				{
					if (uniformVariableDataType == "uniform") // If the string 'uniform' has been found in the source code, do the following
					{
						uniformLayout >> uniformVariableName; // Stream the uniform variable name to the 'uniformVariableName' string

						m_uniformBufferLayout.insert(std::make_pair(uniformVariableName, UniformBufferLayout())); // Insert the shader block name and uniform buffer layout into the uniform buffer layout map

						ShaderBlockName = uniformVariableName; // Set the shader uniform block name string, to the name of the current shader uniform block name

						bFoundShaderUniformBlock = true; // Set 'bFoundShaderUniformBlock' to 'true' (a shader uniform block has been found)

						break; // Break from loop
					}
				}
				else // If the extracted line of source code does not contain a shader uniform block declaration, do the following
				{
					if (uniformVariableDataType == "uniform") // If the string 'uniform' has been found in the source code, do the following
					{
						uniformLayout >> uniformVariableDataType; // Stream the uniform variable data type to the 'uniformVariableDataType' string

						uniformLayout >> uniformVariableName; // Stream the remaining line of source code to the 'uniformVariableName' string (the uniform variable name)

						//uniformVariableName.erase(uniformVariableName.find(';', uniformVariableName.size()));
						uniformVariableName.erase(std::remove(uniformVariableName.begin(), uniformVariableName.end(), ';'), uniformVariableName.end()); // Erase all instnaces of ';' from the string (ignore the character)

						m_UniformLayout.insert(std::make_pair(uniformVariableName, std::make_pair(GLSLStrToSDT(uniformVariableDataType), 0))); // Insert uniform variable data to the map (name, data type and location)

						break; // Break from loop
					}
				}
			}
			else // Else if a shader uniform block has been found, do the following
			{
				if (uniformVariableDataType == "{") // If the current character is '{', do the following
				{
					break; // Break from loop
				}
				else if (uniformVariableDataType == "};") // Else if the current characters are '};', do the following
				{
					bFoundShaderUniformBlock = false; // Set 'bFoundShaderUniformBlock' to 'false' (the end of the shader uniform block)

					break; // Break from loop
				}
				else // Else if the current character is not a bracket (within the shader uniform block), do the following
				{
					if (uniformVariableDataType.find("\t")) // If the current character is a 'tab', do the following
					{
						uniformVariableDataType.erase(std::remove(uniformVariableDataType.begin(), uniformVariableDataType.end(), '\t'), uniformVariableDataType.end()); // Erase all instnaces of '\t' from the string (ignore the character)

						m_uniformBufferLayout.at(ShaderBlockName).addElement(GLSLStrToSDT(uniformVariableDataType)); // Add an shader uniform variable (element) to the current uniform buffer layout instance

						break; // Break from loop
					}
				}
			}
		}
	}

	void OpenGLShader::extractBufferLayout(const std::string& line) // Extract the buffer layout (per-line)
	{
		std::string bufferElement; // String, store each word in the stringstream instance

		std::stringstream bufferLayout(line); // Stringstream instance, store and stream every passed line of vertex shader source code

		bool bFoundElement = false; // Boolean variable, identify whether a buffer layout element has been found or not found within the source code

		while (bufferLayout >> bufferElement) // While the vertex shader source code is streamed to the string, do the following
		{
			if (bFoundElement == false) // If no buffer element has been found, do the following
			{
				if (bufferElement == "in") // If the current word stored in the string is 'in', do the following
				{
					bFoundElement = true; // Set 'bFoundElement' to 'true', a buffer layout element has been found
				}
			}
			else // Else if a buffer layout element has been found, do the following
			{
				break; // Break from the while loop, continue execution of function
			}
		}

		m_ShaderLayout.addElement(GLSLStrToSDT(bufferElement)); // Add the proceeding word from 'in' (e.g. 'vec3') to the buffer layout, must be converted from a string to its corresponding variable first
	}

	void OpenGLShader::parseSource(const std::string & filepath) // Resolve shader source code into its components, compile and link shader components for a single source
	{
		std::fstream m_singleSource(filepath, std::ios::in); // Input stream the source code to an fstream object

		enum { NONE = -1, VERTEX = 0, FRAGMENT } region; // Enumerator container, containing enumerator types of shader source code regions

		if (!m_singleSource.is_open()) // If the source code file could not be opened, do the following
		{
			ENGINE_CRITICAL("Could not open the shader file: {0}", filepath); // Output type 'critical' to the logger console window, output the shader file was not opened
		}

		std::string line; // String, extracts source code on a per-line basis
		std::string src[2]; // Array of strings, used to store the vertex and fragment shader regions of source code

		while (getline(m_singleSource, line)) // For every line in the source code, store in the 'line' string
		{
			// Determine the shader src stype
			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; } // Set the vertex shader data region
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; } // Set the fragment shader data region
			if (line.find("#region Geometry") != std::string::npos) { region = NONE; continue; } // Set the geometry data region
			if (line.find("#region Tessalation") != std::string::npos) { region = NONE; continue; } // Set the tessalation data region

			if (region == VERTEX && line.find("in ") != std::string::npos) // If the region is 'VERTEX' and 'in ' is found within the region and is not at the end position of the string, do the following
			{
				extractBufferLayout(line); // Extract the buffer layout from the current line of source code
			}

			if (bFoundShaderUniformBlock == false) // If 'bFoundShaderUniformBlock' is false (a shader uniform block has not been found), do the following
			{
				if (line.find("uniform ") != std::string::npos) // If the line includes 'uniform ' and is not at the end position of the string, do the following
				{
					if (line.find("layout (std140) uniform ") != std::string::npos) // If the line includes 'layout (std140) uniform ' and is not at the end position of the string, do the following
					{
						extractUniformLayout(line, true); // Extract the uniform layout from the current line of source code (shader uniform block)
					}
					else // Else if a shader uniform block has not been found, do the following
					{
						extractUniformLayout(line, false); // Extract the uniform layout from the current line of source code (single uniform variable)
					}
				}
			}
			else // Else if a shader block has already been found, do the following
			{
				extractUniformLayout(line, true); // Extract the uniform layout from the current line of source code (shader uniform block)
			}

			if (region != NONE) src[region] += (line + "\n"); // If the region is a specified region (#region), set each string in the array to concatenate each line of the chosen region source code, each line starts as a new line ("\n") (instead of paragraphing) 
		}

		m_singleSource.close(); // Close the associated file

		compileAndLink(src[VERTEX], src[FRAGMENT]); // Compile and link shader programme components (vertex and fragments shaders)
	}

	void OpenGLShader::parseSource(const std::string & vertexFilepath, const std::string & fragmentFilepath) // Resolve shader source code into its components, compile and link shader components for multiple sources
	{
		enum { NONE = -1, VERTEX = 0, FRAGMENT } region; // Enumerator container, containing enumerator types of shader source code regions

		std::string line; // String, extracts source code on a per-line basis
		std::string src[2]; // Array of strings, used to store the vertex and fragment shader regions of source code
		
		std::fstream vertexSource(vertexFilepath, std::ios::in); // Input stream the vertex shader source code to an fstream object

		if (!vertexSource.is_open()) // If the source code file could not be opened, do the following
		{
			ENGINE_CRITICAL("Could not open the shader file: {0}", vertexFilepath); // Output type 'critical' to the logger console window, output the shader file was not opened
		}

		while (getline(vertexSource, line)) // For every line in the source code, store in the 'line' string
		{
			if (line.find("in ") != std::string::npos) // If 'in ' is found within the source code but is not at the end position of the string, do the following
			{
				extractBufferLayout(line); // Extract the buffer layout from the current line of source code
			}

			if (bFoundShaderUniformBlock == false) // If 'bFoundShaderUniformBlock' is false (a shader uniform block has not been found), do the following
			{
				if (line.find("uniform ") != std::string::npos) // If the line includes 'uniform ' and is not at the end position of the string, do the following
				{
					if (line.find("layout (std140) uniform ") != std::string::npos) // If the line includes 'layout (std140) uniform ' and is not at the end position of the string, do the following
					{
						extractUniformLayout(line, true); // Extract the uniform layout from the current line of source code
					}
					else // Else if a shader uniform block has not been found, do the following
					{
						extractUniformLayout(line, false); // Extract the uniform layout from the current line of source code (shader uniform block)
					}
				}
			}
			else // Else if a shader block has already been found, do the following
			{
				extractUniformLayout(line, true); // Extract the uniform layout from the current line of source code
			}

			src[VERTEX] += (line + "\n"); // Set a vertex shader string in the array to concatenate each line of vertex region source code, each line starts as a new line ("\n") (instead of paragraphing) 
		}

		vertexSource.close(); // Close the associated file

		std::fstream fragmentSource(fragmentFilepath, std::ios::in); // Input stream the fragment shader source code to an fstream object

		if (!fragmentSource.is_open()) // If the source code file could not be opened, do the following
		{
			ENGINE_CRITICAL("Could not open the shader file: {0}", fragmentFilepath); // Output type 'critical' to the logger console window, output the shader file was not opened
		}

		while (getline(fragmentSource, line)) // For every line in the source code, store in the 'line' string
		{
			if (bFoundShaderUniformBlock == false)
			{
				if (line.find("uniform ") != std::string::npos) // If the line includes 'uniform ' and is not at the end position of the string, do the following
				{
					if (line.find("layout (std140) uniform ") != std::string::npos)
					{
						extractUniformLayout(line, true); // Extract the uniform layout from the current line of source code
					}
					else
					{
						extractUniformLayout(line, false);
					}
				}
			}
			else
			{
				extractUniformLayout(line, true); // Extract the uniform layout from the current line of source code
			}

			src[FRAGMENT] += (line + "\n"); // Set a fragment shader string in the array to concatenate each line of fragment region source code, each line starts as a new line ("\n") (instead of paragraphing) 
		}

		fragmentSource.close(); // Close the associated file

		compileAndLink(src[VERTEX], src[FRAGMENT]); // Compile and link shader programme components (vertex and fragments shaders)
	}

	void OpenGLShader::compileAndLink(const std::string vertexShader, const std::string fragmentShader) // Compile and link shader programme components (vertex and fragments shaders)
	{
		GLint isCompiled = 0; // GL unsigned integer, identfiy whether a shader has compiled or not compiled (boolean values '0' and '1')

		m_vertexSource = vertexShader.c_str(); // Set the vertex shader source code to the passed source code filepath

		glShaderSource(m_vertexShader, 1, &m_vertexSource, 0); // Set the vertex shader object instances source code (replace) to the passed vertex shader source code
		glCompileShader(m_vertexShader); // Compile the vertex shader object instance

		glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &isCompiled); // Get the compile status of the vertex shader object instance
		if (isCompiled == GL_FALSE) // If the vertex shader object instance did not compile (false), do the following
		{
			GLint maxLength = 0; // GL integer, store the length of the vertex shader log message
			glGetShaderiv(m_vertexShader, GL_INFO_LOG_LENGTH, &maxLength); // Get the vertex shader log message length (size)

			std::vector<GLchar> infoLog(maxLength); // Create and set the size of a vector container of GL characters, pass the log length variable
			glGetShaderInfoLog(m_vertexShader, maxLength, &maxLength, &infoLog[0]); // Get the vertex shader log message, store in vector conatiner (update by reference) per character

			ENGINE_CRITICAL("Shader was not compiled, compile error: {0}", std::string(infoLog.begin(), infoLog.end())); // Output type 'critical' to the logger console window, output the shader compile error

			glDeleteShader(m_vertexShader); // Delete the vertex shader object instance

			return; // Return
		}

		m_fragmentSource = fragmentShader.c_str(); // Set the fragment shader source code to the passed source code filepath

		glShaderSource(m_fragmentShader, 1, &m_fragmentSource, 0); // Set the fragment shader object instances source code (replace) to the passed fragment shader source code
		glCompileShader(m_fragmentShader); // Compile the fragment shader object instance

		glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &isCompiled); // Get the compile status of the fragment shader object instance
		if (isCompiled == GL_FALSE) // If the fragment shader object instance did not compile (false), do the following
		{
			GLint maxLength = 0; // GL integer, store the length of the fragment shader log message
			glGetShaderiv(m_fragmentShader, GL_INFO_LOG_LENGTH, &maxLength); // Get the fragment shader log message length (size)

			std::vector<GLchar> infoLog(maxLength); // Create and set the size of a vector container of GL characters, pass the log length variable
			glGetShaderInfoLog(m_fragmentShader, maxLength, &maxLength, &infoLog[0]); // Get the fragment shader log message, store in vector conatiner (update by reference) per character
			
			ENGINE_CRITICAL("Shader was not compiled, compile error: {0}", std::string(infoLog.begin(), infoLog.end())); // Output type 'critical' to the logger console window, output the shader compile error

			glDeleteShader(m_vertexShader); // Delete the vertex shader object instance
			glDeleteShader(m_fragmentShader); // Delete the fragment shader object instance

			return; // Return
		}

		m_OpenGL_ID = glCreateProgram(); // Set m_OpenGL_ID to a rendering program instance

		glAttachShader(m_OpenGL_ID, m_vertexShader); // Attach the vertex shader object instance to the rendering program object instance
		glAttachShader(m_OpenGL_ID, m_fragmentShader);  // Attach the fragment shader object instance to the rendering program object instance
		glLinkProgram(m_OpenGL_ID); // Link the rendering program object instance, create executables of the vertex and fragment shader object instances attached, so they run on their corresponding programmable processors

		GLint isLinked = 0; // GL integer, identify whether the passed rendering program ID has linked to a rendering prgram instance (boolean values '0' and '1')
		
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked); // Get the link status of the rendering program object instance
		if (isLinked == GL_FALSE) // If the rendering program object instance did not link (false), do the following
		{
			GLint maxLength = 0; // GL integer, store the length of the rendering program log message
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength); // Get the rendering program log message length (size)

			std::vector<GLchar> infoLog(maxLength); // Create and set the size of a vector container of GL characters, pass the log length variable
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]); // Get the rendering program log message, store in vector conatiner (update by reference) per character
			
			ENGINE_CRITICAL("Shader(s) were not linked, linking error: {0}", std::string(infoLog.begin(), infoLog.end())); // Output type 'critical' to the logger console window, output the shader(s) linking error

			glDeleteProgram(m_OpenGL_ID); // Delete the rendering program object instance
			glDeleteShader(m_vertexShader); // Delete the vertex shader object instance
			glDeleteShader(m_fragmentShader); // Delete the fragment shader object instance

			return; // Return
		}

		glDetachShader(m_OpenGL_ID, m_vertexShader); // Detach the vertex shader object instance from the rendering program object instance
		glDetachShader(m_OpenGL_ID, m_fragmentShader); // Detach the fragment shader object instance from the rendering program object instance

		glDeleteShader(m_vertexShader); // Delete the vertex shader object instance after linking //-----> additional to given code (delete after detach - free resources)
		glDeleteShader(m_fragmentShader); // Delete the fragment shader object instance after linking //-----> additional to given code (delete after detach - free resources)

	}
}