#pragma once
#include<iostream>

class Texture
{
private:
	unsigned int m_Renderer_id;
	std::string m_file_path;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height,m_BPP;


public:
	Texture(const std::string& path);

	void Bind(unsigned int slot = 0) const;
	void Unbind();
	~Texture();
};