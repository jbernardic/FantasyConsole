#pragma once
#include "TextRenderer.h"
#include <RectangleShape.h>
class TextEditor
{
public:
	TextEditor(TextRenderer& textRenderer);
	void Draw();
	std::vector<std::string> Text{ "" };
	glm::vec2 Position = glm::vec2();
	//position in Text string
	glm::i16vec2 CursorPosition = glm::vec2();
	//returns closest character to x and y in grid
	glm::vec2 FindCursor(int x, int y);
private:
	TextRenderer& m_TextRenderer;
	RectangleShape m_Cursor = RectangleShape(static_cast<float>(m_TextRenderer.LetterSpacing), static_cast<float>(m_TextRenderer.FontSize), 0, 0);
};

