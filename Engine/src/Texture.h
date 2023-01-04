#pragma once
#include<iostream>
#include<string>
#include<iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Texture {
public:
	Texture(const char* path);
	Texture(void* data, int imageWidth, int imageHeight);
	Texture();
	~Texture();
	const void SetData(void* data) const;
	const void Bind() const;
	const void Bind(unsigned int unit) const;
	const void UnBind() const;
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
private:
	int m_Width = 0;
	int m_Height = 0;
	int m_NrChannels = 0;
	unsigned int m_Texture = 0;
	std::string m_Path;
};
