#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uScreenTexture;
uniform sampler2D uOutlineMask;
uniform vec3 uOutlineColor;
uniform vec2 uTexelSize;
uniform float uOutlineWidth;
uniform bool uHasOutline;

float sampleMask(vec2 uv) {return texture(uOutlineMask, uv).r; }

bool isEdge(vec2 uv)
{
	float center = sampleMask(uv);
	if(center > 0.5) return false;

	vec2 offset = uTexelSize * uOutlineWidth;
	float up =		sampleMask(uv + vec2( 0,  offset.y));
	float down =	sampleMask(uv + vec2( 0, -offset.y));
	float left =	sampleMask(uv + vec2( -offset.x, 0));
	float right =	sampleMask(uv + vec2(  offset.x, 0));

	return (up > 0.5 || down > 0.5 || left > 0.5 || right > 0.5);
}

void main()
{
	vec3 color = texture(uScreenTexture, vUV).rgb;

	if(uHasOutline && isEdge(vUV))
		FragColor = vec4(uOutlineColor, 1.0);
	else
		FragColor = vec4(color, 1.0);
}