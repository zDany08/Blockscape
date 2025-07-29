#version 330 core

uniform sampler2D uTex;
uniform float uAmbientLight = 0.2f;

in vec2 vTexCoord;

out vec4 FragColor;

void main() {
	vec4 texColor = texture(uTex, vTexCoord);
	FragColor = texColor * vec4(vec3(uAmbientLight), 1.0f);
}
