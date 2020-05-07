#include <string>

const std::string VSHADER_BASIC = R"glsl(
#version 330 core

layout(location = 0) in vec2 position;
uniform float timeSeconds;

void main() {
	gl_Position = vec4(sin(position.x/200)*500 * sin(timeSeconds+0.2), sin(position.y/200)*500 * sin(timeSeconds*2), sin(timeSeconds), 1.0);
}

)glsl";


const std::string FSHADER_BASIC = R"glsl(
#version 330 core

layout(location = 0) out vec4 color;
uniform float timeSeconds;

void main() {
	color = vec4(sin(gl_FragCoord.x / 320.0)*cos(timeSeconds*2), sin(timeSeconds)*cos(gl_FragCoord.y / 320.0), 0.0, 1.0);
}

)glsl";