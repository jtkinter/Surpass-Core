#version 330 core

in vec2 v_TexCoord;
out vec4 FragColor;

// Ìí¼ÓÎÆÀí½âÊÍÆ÷
uniform sampler2D uTexture;

void main()
{
	FragColor = texture(uTexture, v_TexCoord);
}