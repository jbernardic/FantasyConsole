#pragma once
#include "TextRenderer.h"
#include <RectangleShape.h>
class TextEditor
{
public:
	TextEditor(TextRenderer& textRenderer);
	void Draw();
	std::string Text;
	glm::vec2 Position = glm::vec2();
	int CursorPosition = -1; //position in Text string
private:
	TextRenderer& m_TextRenderer;
	RectangleShape m_Cursor = RectangleShape(m_TextRenderer.LetterSpacing, m_TextRenderer.FontSize, 0, 0);
};

