#include "sppch.h"

#include "Path.h"
#include <algorithm>

namespace Surpass {

	static std::string computeResourceDir()
	{
		std::string file = __FILE__;
		std::replace(file.begin(), file.end(), '\\', '/');

		size_t pos = file.rfind("src/utils/");
		if (pos == std::string::npos) return "";
		return file.substr(0, pos) + "res/";
	}

	const std::string getResourceDir(const std::string& filepath)
	{
		static const std::string shaderDir = computeResourceDir();
		assert(!shaderDir.empty());
		return shaderDir + filepath;
	}

}