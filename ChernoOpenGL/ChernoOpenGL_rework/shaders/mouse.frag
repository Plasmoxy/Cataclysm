#version 330 core

layout(location = 0) out vec4 color;
uniform vec2 u_mouse;
uniform float u_Color;

vec3 hsv2rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    float hue = (u_mouse.x + 1.0)*0.5;
	color = vec4(hsv2rgb(vec3(hue, 1.0, 1.0)).xyz, 1.0);
}