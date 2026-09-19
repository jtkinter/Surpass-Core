#pragma once

namespace Surpass {

	class Texture
	{
	public:
		Texture(const std::string& filepath);
		Texture(int width, int height, const unsigned char* data);
		~Texture();

		void bind(unsigned int unit) const;

	private:
		void setup(int width, int height, const unsigned char* data);

		int m_Width, m_Height, m_BPP;
		unsigned int m_RendererID;
	};

}