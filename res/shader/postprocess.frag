#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uScreenTexture;

void main()
{
	vec3 color = texture(uScreenTexture, vUV).rgb;
	FragColor = vec4(color, 1.0);
}