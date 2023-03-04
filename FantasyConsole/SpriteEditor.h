#pragma once
#include <glm/glm.hpp>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <iostream>
#include <array>
#include "Sprite.h"
#include "SpriteBatch.h"
class SpriteEditor
{
public:
	struct Palette {
		glm::vec4* Colors;
		glm::vec2 Size;
		glm::vec2 Position;
		unsigned int ColumnCount;
		unsigned int ColorCount;
		Palette(glm::vec4* colors, glm::vec2 size, glm::vec2 position, unsigned int columnCount, unsigned int colorCount) {
			Colors = colors;
			Size = size;
			Position = position;
			ColumnCount = columnCount;
			ColorCount = colorCount;
		}
	};
	SpriteEditor(glm::vec2 position, glm::vec2 size, glm::uvec2 gridSize, Palette Palette, Texture* texture);
	void Draw(SpriteBatch& sb);
	void DrawPixel(glm::dvec2 position, glm::vec4 color);
	glm::vec4 PickColor(glm::dvec2 position);
	~SpriteEditor();
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 PickedColors[2]{ glm::vec4(255, 241, 232, 255)/glm::vec4(255), glm::vec4(0.0, 0.0, 0.0, 1.0)};
	unsigned int SpriteIndex = 0;
	bool Active = true;

private:
	Texture* m_Texture;
	std::array<GLubyte, 4> (*m_TextureData)[64];
	Palette m_Pallete;
	glm::uvec2 m_GridSize;
	int m_DrawingColor = -1;
};

