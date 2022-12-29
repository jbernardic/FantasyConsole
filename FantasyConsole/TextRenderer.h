#pragma once
#include <string>
#include "SpriteBatch.h"
class TextRenderer
{
public:
	TextRenderer(const char* texture, glm::vec2 cellSize);
	void Draw(glm::vec2 position, std::string);
	glm::vec2 CellSize;
	unsigned int FontSize = 16;
	unsigned int LineSpacing = 16 + 4;
	unsigned int LetterSpacing = 16 - 3;
	const char* TextureName;
private:
	std::unique_ptr<SpriteBatch> m_SB;
};