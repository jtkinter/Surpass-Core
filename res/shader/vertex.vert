#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	vec4 worldPos = uModel * vec4(aPos, 1.0);
	v_FragPos = worldPos.xyz;
	v_Normal = mat3(uModel) * aNormal;
	v_TexCoord = aTexCoord;

	gl_Position = uProjection * uView * worldPos;
}