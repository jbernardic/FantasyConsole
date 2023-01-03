#pragma once
#include "ResourceManager.h"
#include "glm/glm.hpp"

struct Vertex {
	glm::vec2 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	float TexIndex;
	float IsBitmap;
};

struct Sprite {
	Sprite() {};
	Sprite(Texture* texture);
	Sprite(const char* texture);
	Sprite(const char* texture, unsigned int cellIndex, glm::vec2 cellSize);
	std::array<Vertex, 4> GetVertices(float textureIndex);
	Texture* SpriteTexture = nullptr;
	glm::vec2 Position = glm::vec2();
	glm::vec2 Size = glm::vec2();
	glm::vec4 Color = glm::vec4(1.0);
	glm::vec2 CellSize = glm::vec2();
	unsigned int CellIndex = 0;
	bool IsBitmap = false;

	static Sprite CreateRectangle(glm::vec2 size, glm::vec4 color);
};