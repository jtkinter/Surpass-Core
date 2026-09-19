#include "sppch.h"
#include "TextureGenerator.h"

namespace Surpass {

	std::vector<unsigned char> generatorCheckerBoard(int width, int height, int tileSize)
	{
		std::vector<unsigned char> data(width * height * 4);
		for (int x = 0; x < height; ++x)
		{
			for (int y = 0; y < width; ++y)
			{
				bool write = ((x / tileSize) + (y / tileSize)) % 2 == 0;
				int i = (x * width + y) * 4;
				unsigned char c = write ? 255 : 0;
				data[i] = c;
				data[i + 1] = c;
				data[i + 2] = c;
				data[i + 3] = 255;
			}
		}

		return data;
	}

}