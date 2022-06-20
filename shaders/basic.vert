#version 460 core
layout (location = 0) in vec3 pos1;
uniform vec3 pos2;
void main() {
	gl_Position = vec4(pos1 + pos2, 1);
}
