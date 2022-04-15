#version 330 core

layout(location = 0) out vec4 color;
in vec2 texCoord;

uniform sampler2D texWood;


void main()
{

	color = texture(texWood,texCoord);

}