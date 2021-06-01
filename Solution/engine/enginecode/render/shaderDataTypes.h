/** \file shaderDataTypes.h
*/

#pragma once // Compile once

#include "core/core.h" // Include core.h file

namespace Engine //!< \namespace Engine namespace
{
	/*!
	\class ShaderDataType
	\brief An enumerator type class, containing enumerators of data types
	*/
	enum class ShaderDataType
	{
		None = 0, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, Bool, Sampler2D //!< Shader data types
	};

	//! Convert the shader data type to a size (bytes)
	/*!
	\param dataType A enumerator type representing the shader data type of an element
	*/
	static unsigned int ShaderDataTypeSize(ShaderDataType dataType)
	{
		switch (dataType) //!< Switch case statement, controlled by the passed data type
		{
		case ShaderDataType::Int:		return 4; //!< If the passed data type is of type 'int', return '4' (bytes)
		case ShaderDataType::Int2:		return 4 * 2; //!< If the passed data type is of type 'int2', return '8' (bytes)
		case ShaderDataType::Int3:		return 4 * 3; //!< If the passed data type is of type 'int3', return '12' (bytes)
		case ShaderDataType::Int4:		return 4 * 4; //!< If the passed data type is of type 'int4', return '16' (bytes)
		case ShaderDataType::Float:		return 4; //!< If the passed data type is of type 'float', return '4' (bytes)
		case ShaderDataType::Float2:	return 4 * 2; //!< If the passed data type is of type 'float2', return '8' (bytes)
		case ShaderDataType::Float3:	return 4 * 3; //!< If the passed data type is of type 'float3', return '12' (bytes)
		case ShaderDataType::Float4:	return 4 * 4; //!< If the passed data type is of type 'float4', return '16' (bytes)
		case ShaderDataType::Mat3:		return 4 * 3 * 3; //!< If the passed data type is of type 'mat3', return '36' (bytes)
		case ShaderDataType::Mat4:		return 4 * 4 * 4; //!< If the passed data type is of type 'mat4', return '64' (bytes)
		case ShaderDataType::Bool:		return 1; //!< If the passed data type is of type 'bool', return '1' (bytes)
		case ShaderDataType::Sampler2D: return 1; //!< If the passed data type is of type 'sampler2D', return '1' (bytes)
		}

		return 0; //!< Return '0' (nothing)

	}

	//! Convert the shader data type to their component count (size)
	/*!
	\param dataType A enumerator type representing the shader data type of an element
	*/
	static unsigned int ShaderDataTypeComponentCount(ShaderDataType dataType)
	{
		switch (dataType)  //!< Switch case statement, controlled by the passed data type
		{
		case ShaderDataType::Int:		return 1; //!< If the passed data type is of type 'int', return '1'
		case ShaderDataType::Int2:		return 2; //!< If the passed data type is of type 'int2', return '2'
		case ShaderDataType::Int3:		return 3; //!< If the passed data type is of type 'int3', return '3'
		case ShaderDataType::Int4:		return 4; //!< If the passed data type is of type 'int4', return '4'
		case ShaderDataType::Float:		return 1; //!< If the passed data type is of type 'float', return '1'
		case ShaderDataType::Float2:	return 2; //!< If the passed data type is of type 'float2', return '2'
		case ShaderDataType::Float3:	return 3; //!< If the passed data type is of type 'float3', return '3'
		case ShaderDataType::Float4:	return 4; //!< If the passed data type is of type 'float4', return '4'
		case ShaderDataType::Mat3:		return 3 * 3; //!< If the passed data type is of type 'mat3', return '9'
		case ShaderDataType::Mat4:		return 4 * 4; //!< If the passed data type is of type 'mat4', return '16'
		case ShaderDataType::Bool:		return 1; //!< If the passed data type is of type 'bool', return '1'
		case ShaderDataType::Sampler2D: return 1; //!< If the passed data type is of type 'sampler2D', return '1'
		}

		return 0; //!< Return '0' (nothing)
		
	}
}

