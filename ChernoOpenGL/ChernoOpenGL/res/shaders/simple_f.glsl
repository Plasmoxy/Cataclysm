#version 330 core
layout(location = 0) out vec4 color;

void main()
{
	color = gl_FragCoord;
}