#version 330 core

layout(location = 0) out vec4 color;
in vec4 v_Color;
in vec2 texCoord;

uniform sampler2D texConcrete;
uniform sampler2D texWood;


void main()
{

	color = mix(texture(texConcrete,texCoord),texture(texWood,texCoord),0.5);
	//color = v_Color;
}