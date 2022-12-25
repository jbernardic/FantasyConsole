#pragma once
#include "ResourceManager.h"
#include "glm/glm.hpp"

struct Vertex {
	glm::vec2 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	float TexIndex;
};

class Sprite {
public:
	Sprite(const char* texture, glm::vec2 position = glm::vec2(0.0), glm::vec2 size = glm::vec2(1.0), glm::vec4 color = glm::vec4(1.0));
	std::array<Vertex, 4> GetVertices(float textureIndex);
	Texture& GetTexture();
	static unsigned int Instance;
private:
	Texture* m_Texture;
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	glm::vec4 m_Color;
	glm::vec2 m_TexCoord[4] = {
	 glm::vec2(0.0f, 0.0f),
	 glm::vec2(1.0f, 0.0f),
	 glm::vec2(1.0f,-1.0f),
	 glm::vec2(0.0f,-1.0f),
	};
};

class SpriteSheet {
public:
	SpriteSheet(const char* texture, glm::vec2 spriteSize = glm::vec2(16.0, 16.0));
	std::array<Vertex, 4> GetVertices(unsigned int index);
	Texture& GetTexture();
	static unsigned int Instance;
	void SetTexIndex(unsigned int index) {
		m_TexIndex = static_cast<float>(index);
	}
private:
	Texture* m_Texture;
	glm::vec2 m_SpriteSize;
	float m_TexIndex = 0.0f;
};