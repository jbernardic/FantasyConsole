#include <array>
#include "ResourceManager.h"
#include "Sprite.h"

Sprite::Sprite(Texture* texture)
{
	SpriteTexture = texture;
	Size = glm::vec2(SpriteTexture->GetWidth(), SpriteTexture->GetHeight());
}

Sprite::Sprite(const char* texture) {
	SpriteTexture = &rm::GetTexture(texture);
	Size = glm::vec2(SpriteTexture->GetWidth(), SpriteTexture->GetHeight());
}

Sprite::Sprite(const char* texture, unsigned int cellIndex, glm::vec2 cellSize) : Size(cellSize), CellSize(cellSize), CellIndex(cellIndex) {
	SpriteTexture = &rm::GetTexture(texture);
}

std::array<Vertex, 4> Sprite::GetVertices(float textureIndex) {
	float x = Position.x;
	float y = Position.y;
	float width = Size.x;
	float height = Size.y;
	float texX = 0, texY = 0, texSizeX = 1, texSizeY = 1;

	unsigned int rows = static_cast<unsigned int>(SpriteTexture->GetHeight() / CellSize.y);
	unsigned int columns = static_cast<unsigned int>(SpriteTexture->GetWidth() / CellSize.x);

	//if using sprite sheet
	if(rows != 0 && columns != 0)
	{
		int yIndex = static_cast<int>(CellIndex / columns);
		int xIndex = static_cast<int>(CellIndex % columns);

		texSizeX = CellSize.x / static_cast<float>(SpriteTexture->GetWidth());
		texSizeY = CellSize.y / static_cast<float>(SpriteTexture->GetHeight());

		texX = xIndex * texSizeX;
		texY = yIndex * texSizeY;
	}

	Vertex v0{};
	v0.Position = { x, y + height, };
	v0.Color = Color;
	v0.TexCoord = glm::vec2(texX, texY + texSizeY);
	v0.TexIndex = textureIndex;
	v0.IsBitmap = IsBitmap;
	Vertex v1{};
	v1.Position = { x + width, y + height, };
	v1.Color = Color;
	v1.TexCoord = glm::vec2(texX + texSizeX, texY + texSizeY);
	v1.TexIndex = textureIndex;
	v1.IsBitmap = IsBitmap;
	Vertex v2{};
	v2.Position = { x + width, y};
	v2.Color = Color;
	v2.TexCoord = glm::vec2(texX + texSizeX, texY);
	v2.TexIndex = textureIndex;
	v2.IsBitmap = IsBitmap;
	Vertex v3{};
	v3.Position = { x, y, };
	v3.Color = Color;
	v3.TexCoord = glm::vec2(texX, texY);
	v3.TexIndex = textureIndex;
	v3.IsBitmap = IsBitmap;

	if (SpriteTexture == &rm::GetEmptyTexture()) {
		v0.TexCoord = glm::vec2(-1.0f);
		v1.TexCoord = glm::vec2(-1.0f);
		v2.TexCoord = glm::vec2(-1.0f);
		v3.TexCoord = glm::vec2(-1.0f);
	}

	return { v0, v1, v2, v3 };
}

Sprite Sprite::CreateRectangle(glm::vec2 size, glm::vec4 color)
{
	Sprite sprite(&rm::GetEmptyTexture());
	sprite.Size = size;
	sprite.Color = color;
	return sprite;
}
