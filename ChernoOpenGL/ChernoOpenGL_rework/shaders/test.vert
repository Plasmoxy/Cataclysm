#version 330 core

// layout(location=0) means that this variable will be bound to attribute with index 0
layout(location = 0) in vec2 position;
uniform float u_Secs;

float rand(float x) {
    return fract(sin(dot(vec2(1.0, x),vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	gl_Position = vec4(2*position.x * rand(u_Secs), 2*position.y * rand(u_Secs+1), 0.0, 1.0);
}