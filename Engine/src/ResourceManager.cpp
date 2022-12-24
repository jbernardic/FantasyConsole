#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

void ResourceManager::LoadShader(const char* path, std::string name) {
	shaders[name] = Shader(path);
}
Shader& ResourceManager::GetShader(std::string name) {
	return shaders[name];
}
void ResourceManager::LoadTexture(const char* path, std::string name) {
	textures[name] = Texture(path);
}
Texture& ResourceManager::GetTexture(std::string name) {
	return textures[name];
}
void ResourceManager::DeleteAllShaders() {
	for (const std::pair<std::string, Shader>& _shader : shaders) {
		const Shader& shader = _shader.second;
		glDeleteShader(shader.GetID());
	}
}