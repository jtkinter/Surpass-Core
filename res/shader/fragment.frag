#version 330 core

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;
in vec4 v_LightSpacePos;

out vec4 FragColor;

uniform sampler2D uTexture; // 纹理解释器
uniform vec3 uViewPos;		// 相机位置
uniform sampler2D uShadowMap;

const int MAX_LIGHTS = 8;
uniform int uLightCount;
uniform vec3 uLightPos[MAX_LIGHTS];		// 光源位置
uniform vec3 uLightColor[MAX_LIGHTS];	// 光源颜色

float calculateShadow(vec4 lightSpacePos, vec3 norm, vec3 lightDir)
{
	vec3 proj = lightSpacePos.xyz / lightSpacePos.w;
	proj = proj * 0.5 + 0.5;
	if(proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0 || proj.z < 0.0 || proj.z > 1.0)
		return 0.0;

	float closestDepth = texture(uShadowMap, proj.xy).r;
	float currentDepth = proj.z;

	float bias = max(0.001 * (1.0 - dot(norm, lightDir)), 0.0001);
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
	
	return shadow;
}

void main()
{
	vec4 texColor = texture(uTexture, v_TexCoord);
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(uViewPos - v_FragPos);

	vec3 result = vec3(0.0f);
	float ambientStrength = 0.3;
	vec3 ambient = vec3(0.0f);

	vec3 mainLightDir = normalize(uLightPos[0] - v_FragPos);
	float shadow = calculateShadow(v_LightSpacePos, norm, mainLightDir);

	for(int i = 0; i < uLightCount; ++i)
	{
		vec3 lightDir = normalize(uLightPos[i] - v_FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);

		// 环境光
		ambient += ambientStrength * uLightColor[i];

		// 漫反射
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * uLightColor[i];

		// 镜面反射
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
		vec3 specular = 0.5 * spec * uLightColor[i];

		// 阴影
		float lightShadow = (i == 0) ? (1.0 - shadow) : 1.0;

		result += (diffuse + specular) * lightShadow;
	}
	result += ambient / vec3(uLightCount);
	
	FragColor = vec4(result * texColor.rgb, texColor.a);
}