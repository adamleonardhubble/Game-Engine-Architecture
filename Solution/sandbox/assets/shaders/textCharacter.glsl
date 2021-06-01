#region Vertex

#version 440 core
			
layout(location = 0) in vec2 a_vertexPosition;
layout(location = 1) in vec2 a_texCoord;

out vec2 texCoord;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

void main()
{
	texCoord = a_texCoord;
	gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition, 0, 1);
}

#region Fragment

#version 440 core
			
layout(location = 0) out vec4 colour;

in vec2 texCoord;

uniform sampler2D u_texData;
uniform vec3 u_fontColour;

void main()
{
	colour = vec4(1.0, 1.0, 1.0, texture(u_texData, texCoord).r) * vec4(u_fontColour, 1.0);
}