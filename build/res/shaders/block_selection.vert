#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec4 uColor;
uniform mat4 uProjection;
uniform mat4 uView;

out vec4 vColor;

void main() {
	gl_Position = uProjection * uView * vec4(aPos, 1.0);
	vColor = uColor;
}
