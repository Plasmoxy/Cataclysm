#version 330 core

// layout(location=0) means that this variable will be bound to attribute with index 0
layout(location = 0) in vec2 position;
uniform float u_Secs;

void main() {
	gl_Position = vec4(position.xy, 0.0, 1.0);
}