#version 330 core

out vec4 color;
uniform vec4 changingColor;

void main() {
	color = changingColor;
}