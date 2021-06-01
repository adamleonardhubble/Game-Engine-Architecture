#version 440 core
			
layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexNormal;
layout(location = 2) in vec2 a_texCoord;

out vec3 fragmentPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 u_model;
uniform mat4 u_MVP;

void main()
{
	fragmentPos = vec3(u_model * vec4(a_vertexPosition, 1.0));
	normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
	texCoord = vec2(a_texCoord.x, a_texCoord.y);
	gl_Position =  u_MVP * vec4(a_vertexPosition,1.0);
}