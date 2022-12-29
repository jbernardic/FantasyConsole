#pragma once
#include "TextRenderer.h"
#include <RectangleShape.h>
class TextEditor
{
public:
	TextEditor(TextRenderer& textRenderer);
	void Draw();
	std::string Text;
	std::vector<unsigned int> LinePositions;
	glm::vec2 Position = glm::vec2();
	//position in Text string
	glm::vec2 CursorPosition = glm::vec2();
	//from grid position
	unsigned int FindCursorPosition(unsigned int x, unsigned int y);
	//returns closest character to cursor
	glm::vec2 FindCursor();
private:
	TextRenderer& m_TextRenderer;
	RectangleShape m_Cursor = RectangleShape(static_cast<float>(m_TextRenderer.LetterSpacing), static_cast<float>(m_TextRenderer.FontSize), 0, 0);
};

