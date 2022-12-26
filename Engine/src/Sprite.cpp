#include <array>
#include "ResourceManager.h"
#include "Sprite.h"

Sprite::Sprite(const char* texture) {
	Texture = &rm::GetTexture(texture);
	Size = glm::vec2(Texture->GetWidth(), Texture->GetHeight());
}

Sprite::Sprite(const char* texture, unsigned int cellIndex, glm::vec2 cellSize) : Size(cellSize), CellSize(cellSize), CellIndex(cellIndex) {
	Texture = &rm::GetTexture(texture);
}

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
		int yIndex = static_cast<int>(CellIndex / columns);
		int xIndex = static_cast<int>(CellIndex % columns);

		texSizeX = CellSize.x / static_cast<float>(Texture->GetWidth());
		texSizeY = CellSize.y / static_cast<float>(Texture->GetHeight());

		texX = xIndex * texSizeX;
		texY = yIndex * texSizeY;
	}

	Vertex v0{};
	v0.Position = { x, y + height, };
	v0.Color = glm::vec4(1.0);
	v0.TexCoord = glm::vec2(texX, texY + texSizeY);
	v0.TexIndex = textureIndex;
	v0.IsBitmap = IsBitmap;
	Vertex v1{};
	v1.Position = { x + width, y + height, };
	v1.Color = glm::vec4(1.0);
	v1.TexCoord = glm::vec2(texX + texSizeX, texY + texSizeY);
	v1.TexIndex = textureIndex;
	v1.IsBitmap = IsBitmap;
	Vertex v2{};
	v2.Position = { x + width, y};
	v2.Color = glm::vec4(1.0);
	v2.TexCoord = glm::vec2(texX + texSizeX, texY);
	v2.TexIndex = textureIndex;
	v2.IsBitmap = IsBitmap;
	Vertex v3{};
	v3.Position = { x, y, };
	v3.Color = glm::vec4(1.0);
	v3.TexCoord = glm::vec2(texX, texY);
	v3.TexIndex = textureIndex;
	v3.IsBitmap = IsBitmap;

	return { v0, v1, v2, v3 };
}
