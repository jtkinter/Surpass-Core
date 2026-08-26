#include "sppch.h"
#include "utils.h"
#include <fstream>
#include <sstream>

// 读取glsl源文件
std::string readShaderFile(const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		std::cerr << "错误：无法打开着色器文件: " << filepath << std::endl;
		return "";
	}

	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}