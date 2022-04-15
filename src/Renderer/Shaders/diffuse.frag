#version 330 core

layout(location = 0) out vec4 out_color;
in vec2 texCoord;

in vec3 normal;
in vec3 l_Pos;
in vec4 l_Color;
in float l_Intensity;


uniform sampler2D texWood;


void main()
{

	float kd = dot(l_Pos,normal);
	vec4 diffColor = texture(texWood,texCoord);

	

	out_color = (kd*diffColor)*(l_Intensity*l_Color) ;

}