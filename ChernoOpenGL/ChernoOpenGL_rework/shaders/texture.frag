#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform float u_Negative;

void main() {
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = vec4(abs(vec3(u_Negative, u_Negative, u_Negative) - texColor.xyz), 1);
}