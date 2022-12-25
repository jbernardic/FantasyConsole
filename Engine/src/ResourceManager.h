#pragma once
#include <iostream>
#include<map>
#include <string>
#include "Shader.h"
#include "Texture.h"

#define rm ResourceManager

class ResourceManager {
public:
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;

	static void LoadShader(const char* path, std::string name);

	static Shader& GetShader(std::string name);
	static std::map<std::string, Shader>& GetShaders() {
		return shaders;
	}
	static void LoadTexture(const char* path, std::string name);
	static Texture& GetTexture(std::string name);
	static std::map<std::string, Texture>& GetTextures() {
		return textures;
	}
	static void DeleteAllShaders();
private:
	ResourceManager();
};
