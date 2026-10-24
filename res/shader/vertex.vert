#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 aTangent;

const int MAX_LIGHTS = 8;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec4 v_Tangent;
out vec3 v_FragPos;
out vec4 v_LightSpacePos[MAX_LIGHTS];

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightSpaceMatrices[MAX_LIGHTS];

void main()
{
	vec4 worldPos = uModel * vec4(aPos, 1.0);
	v_FragPos = worldPos.xyz;

	mat3 normalMatrix = mat3(uModel);
	v_Normal = normalize(normalMatrix * aNormal);
	v_Tangent = vec4(normalize(normalMatrix * aTangent.xyz), aTangent.w);
	v_TexCoord = aTexCoord;
	for(int i = 0; i < MAX_LIGHTS; ++i)
		v_LightSpacePos[i] = uLightSpaceMatrices[i] * worldPos;

	gl_Position = uProjection * uView * worldPos;
}