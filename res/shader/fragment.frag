#version 330 core

const int MAX_LIGHTS = 8;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;
in vec4 v_LightSpacePos[MAX_LIGHTS];

out vec4 FragColor;

// 材质
uniform vec3 uBaseColor;
uniform sampler2D uDiffuseMap;
uniform bool uHasDiffuseMap;
uniform float uShininess;

// 光照相机参数（投影）

uniform vec3 uViewPos;			// 相机位置
uniform sampler2D uShadowMap[MAX_LIGHTS];	// 深度图
uniform int uLightToShadow[MAX_LIGHTS];
// uniform int uShadowLightCount;  // 暂时没用

// 光亮
uniform int uLightCount;
uniform vec3 uLightPos[MAX_LIGHTS];		// 光源位置
uniform vec3 uLightColor[MAX_LIGHTS];	// 光源颜色

float calculateShadow(int shadowIndex, vec4 lightSpacePos, vec3 norm, vec3 lightDir)
{
	vec3 proj = lightSpacePos.xyz / lightSpacePos.w;
	proj = proj * 0.5 + 0.5;
	if(proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0 || proj.z < 0.0 || proj.z > 1.0)
		return 0.0;

	float bias = max(0.0025 * (1.0 - dot(norm, lightDir)), 0.0001);
	float currentDepth = proj.z - bias;

	vec2 texelSize = 1.0 / vec2(textureSize(uShadowMap[shadowIndex], 0));
	float shadow = 0.0;
	int radius = 3;

	for(int x = -radius; x <= radius; ++x)
	{
		for(int y = -radius; y <= radius; ++y)
		{
			float closestDepth = texture(uShadowMap[shadowIndex], proj.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth > closestDepth ? 1.0 : 0.0;
		}
	}
	float samples = (radius * 2 + 1) * (radius * 2 + 1);
	shadow /= samples;
	
	return shadow;
}

void main()
{
	vec3 baseColor = uBaseColor;
	if (uHasDiffuseMap)
		baseColor *= texture(uDiffuseMap, v_TexCoord).rgb;
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(uViewPos - v_FragPos);

	vec3 result = vec3(0.0f);
	float ambientStrength = 0.3;
	vec3 ambient = vec3(0.0f);

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
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
		vec3 specular = 0.5 * spec * uLightColor[i];

		// 阴影
		float lightShadow = 1.0;
		int s = uLightToShadow[i];
		if(s >= 0)
			lightShadow = 1.0 - calculateShadow(s, v_LightSpacePos[s], norm, lightDir);

		result += (diffuse + specular) * lightShadow;
	}
	result += ambient / vec3(uLightCount);
	
	FragColor = vec4(result * baseColor, 1.0);
}