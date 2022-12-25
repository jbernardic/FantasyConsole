#include <array>
#include "ResourceManager.h"
#include "Sprite.h"

Sprite::Sprite(const char* texture, glm::vec2 position, glm::vec2 size, glm::vec4 color) : m_Position(position), m_Size(size), m_Color(color) {
	m_Texture = &rm::GetTexture(texture);
	Instance++;
}

std::array<Vertex, 4> Sprite::GetVertices(float textureIndex) {
	//position
	float x = m_Position.x;
	float y = m_Position.y;
	float width = m_Size.x;
	float height = m_Size.y;

	Vertex v0{};
	v0.Position = { x, y + height, };
	v0.Color = m_Color;
	v0.TexCoord = m_TexCoord[0];
	v0.TexIndex = textureIndex;
	Vertex v1{};
	v1.Position = { x + width, y + height, };
	v1.Color = m_Color;
	v1.TexCoord = m_TexCoord[1];
	v1.TexIndex = textureIndex;
	Vertex v2{};
	v2.Position = { x + width, y, };
	v2.Color = m_Color;
	v2.TexCoord = m_TexCoord[2];
	v2.TexIndex = textureIndex;
	Vertex v3{};
	v3.Position = { x, y, };
	v3.Color = m_Color;
	v3.TexCoord = m_TexCoord[3];
	v3.TexIndex = textureIndex;

	return { v0, v1, v2, v3 };
}

Texture& Sprite::GetTexture()
{
	return *m_Texture;
}