#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

uniform mat4 MVP;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform float lightIntensity;

out vec2 texCoord;

out vec3 l_Pos;
out vec4 l_Color;
out float l_Intensity;

out vec3 normal;


void main()
{
	

	l_Pos = lightPos;
	l_Color = lightColor;
	l_Intensity = lightIntensity;

	normal = inNormal;

	texCoord = inTexCoord;
	gl_Position = MVP * vec4(inPos,1.0);
}