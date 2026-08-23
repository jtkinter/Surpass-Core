#version 330 core
out vec4 FragColor;
uniform float uGreen;
void main() {
	FragColor = vec4(1.0f, uGreen, 0.2f, 1.0f);
}