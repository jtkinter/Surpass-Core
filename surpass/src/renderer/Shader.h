#pragma once

#include <string>
#include <unordered_map>

class Shader 
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use() const;
	void setUniform1f(const std::string& name, float value) const;

private:
	unsigned int compileShader(unsigned int type, const char* source);
	int getUniformLocation(const std::string& name) const;
	
	unsigned int m_ID;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
};