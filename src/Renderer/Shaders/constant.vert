#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 colorPassed;

uniform mat4 MVP;
out vec4 v_Color;

void main()
{
	v_Color = vec4(colorPassed,1.0);
	gl_Position = MVP * vec4(pos,1.0);
}