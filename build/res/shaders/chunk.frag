#version 330 core

uniform sampler2D uTex;

in vec2 vTexCoord;

out vec4 FragColor;

void main() {
	vec4 texColor = texture(uTex, vTexCoord);
	if (texColor.a < 0.5) discard;
	FragColor = texColor;
}
