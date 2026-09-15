#version 330 core

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

out vec4 FragColor;

uniform sampler2D uTexture; // 纹理解释器
uniform vec3 uLightPos;		// 光源位置
uniform vec3 uLightColor;	// 光源颜色
uniform vec3 uViewPos;		// 相机位置

void main()
{
//	vec4 texColor = texture(uTexture, v_TexCoord);
	vec4 texColor = vec4(0.8, 0.6, 0.4, 1.0);

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(uLightPos - v_FragPos);
	vec3 viewDir = normalize(uViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	// 环境光
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * uLightColor;

	// 漫反射
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * uLightColor;

	// 镜面反射
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	vec3 specular = 0.5 * spec * uLightColor;

	vec3 result = (ambient + diffuse + specular) * texColor.rgb;
	FragColor = vec4(result, texColor.a);
}