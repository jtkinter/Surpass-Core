#pragma once

namespace Surpass {
	std::vector<unsigned char> generatorCheckerBoard(int width, int height, int tileSize);
	std::vector<unsigned char> generatorNormalMap(int width, int height, int freq);
}