#pragma once
#include<GLM/glm.hpp>
#include "RectangleShape.h"
#include "Texture.h"
#define MaxSpriteCount 1000

struct Vertex {
	glm::vec2 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	float TexIndex;
};

class Sprite {
public:
	Sprite(const char* texturePath, glm::vec2 position = glm::vec2(0.0), glm::vec2 size = glm::vec2(1.0), glm::vec4 color = glm::vec4(1.0));
	std::array<Vertex, 4> GetVertices();
	Texture& GetTexture();
	static unsigned int instance;
	void SetTexIndex(unsigned int index) {
		m_TexIndex = static_cast<float>(index);
	}
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
	float m_TexIndex = 0.0f;
};

class SpriteBatch{
public:
	SpriteBatch();
	void Draw(Sprite& sprite);
	void End();
	void Start();
	static unsigned int instance;
private:
	size_t verticies_size = 0;
	Shader* shader;
	std::unique_ptr<IndexBuffer> ib;
	VertexArray va;
	VertexBuffer vb = VertexBuffer(MaxSpriteCount*sizeof(Vertex));
};
