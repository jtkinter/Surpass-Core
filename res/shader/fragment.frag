#version 330 core

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

out vec4 FragColor;

uniform sampler2D uTexture; // 纹理解释器
uniform vec3 uViewPos;		// 相机位置

const int MAX_LIGHTS = 8;
uniform int uLightCount;
uniform vec3 uLightPos[MAX_LIGHTS];		// 光源位置
uniform vec3 uLightColor[MAX_LIGHTS];	// 光源颜色

void main()
{
	vec4 texColor = texture(uTexture, v_TexCoord);
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
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
		vec3 specular = 0.5 * spec * uLightColor[i];

		result += diffuse + specular;
	}
	result += ambient / vec3(uLightCount);
	
	FragColor = vec4(result * texColor.rgb, texColor.a);
}