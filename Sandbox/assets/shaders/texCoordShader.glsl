#type vertex
#version 330 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_modelMatrix;

out vec2 v_TexCoord;

void main() 
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_viewProjection * u_modelMatrix * vec4(a_Pos, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() 
{
	color = vec4(v_TexCoord, 0.0, 1.0);
}