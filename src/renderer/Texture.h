#pragma once

namespace Surpass {

	class Texture
	{
	public:
		Texture() = default;
		Texture(const std::string& filepath);
		Texture(int width, int height, const unsigned char* data);
		~Texture();

		void init(const std::string& filepath);
		void init(int width, int height, const unsigned char* data);

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(const Texture&&) = delete;

		void bind(unsigned int unit) const;

	private:
		void destroy();

		int m_Width = 0, m_Height = 0, m_BPP = 0;
		unsigned int m_RendererID = 0;
	};

}