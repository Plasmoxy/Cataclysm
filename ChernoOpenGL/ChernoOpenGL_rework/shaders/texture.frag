#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = vec4(vec3(1, 1, 1) - texColor.xyz, 1);
}