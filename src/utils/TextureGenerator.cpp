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

	std::vector<unsigned char> generatorNormalMap(int width, int height, int freq)
	{
		std::vector<unsigned char> data(width * height * 4);
		for (int x = 0; x < height; ++x)
		{
			for (int y = 0; y < width; ++y)
			{
				float dx = std::cos(2.0f * glm::pi<float>() * freq * x / height);
				float dy = std::cos(2.0f * glm::pi<float>() * freq * y / width);

				glm::vec3 n = glm::normalize(glm::vec3(-dy * 0.5f, -dx * 0.5f, 1.0f));

				int i = (x * width + y) * 4;
				data[i] = (unsigned char)((n.x * 0.5f + 0.5f) * 255);
				data[i+1] = (unsigned char)((n.y * 0.5f + 0.5f) * 255);
				data[i+2] = (unsigned char)((n.z * 0.5f + 0.5f) * 255);
				data[i+3] = 255;
			}
		}

		return data;
	}

}