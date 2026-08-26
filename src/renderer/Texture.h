#pragma once

class Texture 
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(unsigned int unit) const;

private:
	int m_Width, m_Height, m_BPP;
	unsigned int m_RendererID;
};