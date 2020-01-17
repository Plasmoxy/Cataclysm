#version 330 core
layout(location = 0) in vec4 position; // autocast to vec4

void main()
{
	gl_Position = position;
}

