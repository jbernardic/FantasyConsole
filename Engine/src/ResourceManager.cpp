#include "ResourceManager.h"

std::map<std::string, std::unique_ptr<Shader>> ResourceManager::Shaders;
std::map<std::string, std::unique_ptr<Texture>> ResourceManager::Textures;

void ResourceManager::LoadShader(const char* path, std::string name) {
	if (Shaders.count(name) == 0) {
		Shaders[name] = std::make_unique<Shader>(path);
	}
}
Shader& ResourceManager::GetShader(std::string name) {
	return *Shaders[name];
}
void ResourceManager::LoadTexture(const char* path, std::string name) {
	Textures[name] = std::make_unique<Texture>(path);
}
Texture& ResourceManager::GetTexture(std::string name) {
	return *Textures[name];
}