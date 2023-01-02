#pragma once
#include <string>
#include "SpriteBatch.h"
class TextRenderer
{
public:
	TextRenderer(const char* texture, glm::vec2 cellSize);
	void Draw(glm::vec2 position, std::string text);
	glm::vec2 CellSize;
	unsigned int FontSize = 8;
	unsigned int LineSpacing = 8 + 2;
	unsigned int LetterSpacing = 8;
	bool Uppercase = false;
	const char* TextureName;
private:
	std::unique_ptr<SpriteBatch> m_SB;
};