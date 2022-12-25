#pragma once
#include "ResourceManager.h"
#include "glm/glm.hpp"

struct Vertex {
	glm::vec2 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	float TexIndex;
};

struct Sprite {
	Sprite(const char* texture);
	Sprite(const char* texture, unsigned int cellIndex, glm::vec2 cellSize);
	std::array<Vertex, 4> GetVertices(float textureIndex);
	Texture* Texture;
	glm::vec2 Position = glm::vec2();
	glm::vec2 Size = glm::vec2();
	glm::vec4 Color = glm::vec4(1.0);
	glm::vec2 CellSize = glm::vec2();
	unsigned int CellIndex = 0;
};

//class SpriteSheet {
//public:
//	SpriteSheet(const char* texture, glm::vec2 spriteSize = glm::vec2(16.0, 16.0));
//	std::array<Vertex, 4> GetVertices(float textureIndex, unsigned int spriteIndex, glm::vec2 position, glm::vec2 size);
//	Texture& GetTexture() { return *m_Texture; };
//	static unsigned int Instance;
//private:
//	Texture* m_Texture;
//	glm::vec2 m_SpriteSize;
//};