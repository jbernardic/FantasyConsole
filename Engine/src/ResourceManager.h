#pragma once
#include <iostream>
#include<map>
#include <string>
#include "Shader.h"
#include "Texture.h"

#define rm ResourceManager

class ResourceManager {
public:
	static std::map<std::string, std::unique_ptr<Shader>> Shaders;
	static std::map<std::string, std::unique_ptr<Texture>> Textures;

	static void LoadShader(const char* path, std::string name);

	static Shader& GetShader(std::string name);
	static void LoadTexture(const char* path, std::string name);
	static Texture& GetTexture(std::string name);
	static Texture& GetEmptyTexture();
private:
	static std::unique_ptr<Texture> m_EmptyTexture;
};
