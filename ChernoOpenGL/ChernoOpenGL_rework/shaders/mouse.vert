#version 330 core

layout(location = 0) in vec2 pos;
uniform vec2 u_mouse;

void main() {
	float x;
	float y;
	if (pos.x < 0) {
		x = u_mouse.x;
		y = u_mouse.y;
	} else {
		x = pos.x;
		y = pos.y;
	}
	
	gl_Position = vec4(x, y, 0.0, 1.0);
}