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
	SpriteEditor(glm::vec2 position, glm::vec2 size, unsigned int gridWidth, unsigned int gridHeight, Palette Palette);
	void Draw(SpriteBatch& sb);
	void DrawPixel(glm::dvec2 position);
	~SpriteEditor();
	glm::vec2 Position;
	glm::vec2 Size;
	bool Active = true;

private:
	Palette m_Pallete;
	glm::uvec2 m_GridSize;
	Sprite* m_Grid;
	bool m_Drawing = false;
};

