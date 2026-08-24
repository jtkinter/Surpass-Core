#include "Shader.h"
#include "utils/Utils.h"
#include <iostream>
#include <glad/glad.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexShaderSource = readShaderFile(vertexPath);
	std::string fragmentShaderSource = readShaderFile(fragmentPath);
	if (vertexShaderSource.empty() || fragmentShaderSource.empty())
	{
		std::cerr << "着色器文件读取失败" << std::endl;
		return;
	}

	const char* vertexShaderSrc = vertexShaderSource.c_str();
	const char* fragmentShaderSrc = fragmentShaderSource.c_str();

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);

	int success;
	char infoLog[512];
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_ID, 512, NULL, infoLog);
		std::cerr << "着色器程序链接失败: " << infoLog << std::endl;
	}

	// 清理着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::use() const
{
	glUseProgram(m_ID);
}

void Shader::setUniform1f(const std::string& name, float value) const
{
	glUniform1f(getUniformLocation(name), value);
}

// 创造并编译着色器
unsigned int Shader::compileShader(unsigned int type, const char* source)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);

	int success;
	char infoLog[512];
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << (type == GL_VERTEX_SHADER ? "顶点" : "片段") << "着色器编译失败: " << infoLog << std::endl;
	}
	return shader;
}

// 获取uniform位置，缓存起来避免每帧查询
int Shader::getUniformLocation(const std::string& name) const
{
	auto it = m_UniformLocationCache.find(name);

	int location;
	if (it != m_UniformLocationCache.end())
		location = it->second;
	else
	{
		location = glGetUniformLocation(m_ID, name.c_str());
		m_UniformLocationCache[name] = location;
	}

	if (location == -1)
		std::cerr << "警告：Uniform '" << name << "' 在着色器中未找到" << std::endl;

	return location;
}