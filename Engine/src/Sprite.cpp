#include <array>
#include "ResourceManager.h"
#include "Sprite.h"

//unsigned int SpriteSheet::Instance = 0;

Sprite::Sprite(const char* texture) {
	Texture = &rm::GetTexture(texture);
	Size = glm::vec2(Texture->GetWidth(), Texture->GetHeight());
}

Sprite::Sprite(const char* texture, unsigned int cellIndex, glm::vec2 cellSize) : Size(cellSize), CellSize(cellSize), CellIndex(cellIndex) {
	Texture = &rm::GetTexture(texture);
}

//std::array<Vertex, 4> Sprite::GetVertices(float textureIndex) {
//	float x = m_Position.x;
//	float y = m_Position.y;
//	float width = m_Size.x;
//	float height = m_Size.y;
//
//	Vertex v0{};
//	v0.Position = { x, y + height, };
//	v0.Color = m_Color;
//	v0.TexCoord = m_TexCoord[0];
//	v0.TexIndex = textureIndex;
//	Vertex v1{};
//	v1.Position = { x + width, y + height, };
//	v1.Color = m_Color;
//	v1.TexCoord = m_TexCoord[1];
//	v1.TexIndex = textureIndex;
//	Vertex v2{};
//	v2.Position = { x + width, y, };
//	v2.Color = m_Color;
//	v2.TexCoord = m_TexCoord[2];
//	v2.TexIndex = textureIndex;
//	Vertex v3{};
//	v3.Position = { x, y, };
//	v3.Color = m_Color;
//	v3.TexCoord = m_TexCoord[3];
//	v3.TexIndex = textureIndex;
//
//	return { v0, v1, v2, v3 };
//}
//
//SpriteSheet::SpriteSheet(const char* texture, glm::vec2 spriteSize) : m_SpriteSize(spriteSize) {
//	m_Texture = &rm::GetTexture(texture);
//	Instance++;
//}
std::array<Vertex, 4> Sprite::GetVertices(float textureIndex) {
	float x = Position.x;
	float y = Position.y;
	float width = Size.x;
	float height = Size.y;
	float texX = 0, texY = 0, texSizeX = 1, texSizeY = 1;

	unsigned int rows = static_cast<unsigned int>(Texture->GetHeight() / CellSize.y);
	unsigned int columns = static_cast<unsigned int>(Texture->GetWidth() / CellSize.x);

	//if using sprite sheet
	if(rows != 0 && columns != 0)
	{
		int a = static_cast<int>(CellIndex / columns);
		int b = static_cast<int>(CellIndex % columns);
		texY = a / static_cast<float>(rows);
		texX = b / static_cast<float>(columns);

		texSizeX = 1.0f / static_cast<float>(columns);
		texSizeY = 1.0f / static_cast<float>(rows);
	}

	Vertex v0{};
	v0.Position = { x, y + height, };
	v0.Color = glm::vec4(1.0);
	v0.TexCoord = glm::vec2(texX, texY + texSizeY);
	v0.TexIndex = textureIndex;
	Vertex v1{};
	v1.Position = { x + width, y + height, };
	v1.Color = glm::vec4(1.0);
	v1.TexCoord = glm::vec2(texX + texSizeX, texY + texSizeY);
	v1.TexIndex = textureIndex;
	Vertex v2{};
	v2.Position = { x + width, y};
	v2.Color = glm::vec4(1.0);
	v2.TexCoord = glm::vec2(texX + texSizeX, texY);
	v2.TexIndex = textureIndex;
	Vertex v3{};
	v3.Position = { x, y, };
	v3.Color = glm::vec4(1.0);
	v3.TexCoord = glm::vec2(texX, texY);
	v3.TexIndex = textureIndex;

	return { v0, v1, v2, v3 };
}
