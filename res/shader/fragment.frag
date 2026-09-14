#version 330 core

in vec2 v_TexCoord;
out vec4 FragColor;

// ÃÌº”Œ∆¿ÌΩ‚ Õ∆˜
uniform sampler2D uTexture;

void main()
{
//	FragColor = texture(uTexture, v_TexCoord);
	FragColor = vec4(0.8, 0.6, 0.4, 1.0);
}