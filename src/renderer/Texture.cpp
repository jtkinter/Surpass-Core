#include "sppch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Surpass {

	Texture::Texture(const std::string& filepath)
	{
		init(filepath);
	}

	Texture::Texture(int width, int height, const unsigned char* data)
	{
		init(width, height, data);
	}

	Texture::~Texture()
	{
		destroy();
	}

	void Texture::init(const std::string& filepath)
	{
		destroy();

		stbi_set_flip_vertically_on_load(1);
		int width, height, bpp;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);
		if (!data)
		{
			std::cerr << "纹理加载失败" << std::endl;
			return;
		}
		init(width, height, data);
		stbi_image_free(data);
	}

	void Texture::init(int width, int height, const unsigned char* data)
	{
		destroy();

		m_Width = width;
		m_Height = height;
		m_BPP = 4;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		// 设置环绕和过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::bind(unsigned int unit) const
	{
		// 激活GPU插孔
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Texture::destroy()
	{
		if (m_RendererID)
			glDeleteTextures(1, &m_RendererID);
		m_RendererID = m_Width = m_Height = m_BPP = 0;
	}

}