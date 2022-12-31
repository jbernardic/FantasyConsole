#include "TextRenderer.h"
#include <Window.h>
#include "RectangleShape.h"

TextRenderer::TextRenderer(const char* texture, glm::vec2 cellSize) : TextureName(texture), CellSize(cellSize) {
	m_SB = std::make_unique<SpriteBatch>();
}

void TextRenderer::Draw(glm::vec2 position, std::string text) {
	unsigned int x = 0;
	unsigned int y = 0;
	m_SB->Begin();
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == '\n') {
			y += LineSpacing;
			x = 0;
			continue;
		}
		unsigned int codepoint = text[i];
		if (Uppercase && codepoint >= 97 && codepoint <= 122) codepoint -= 32; //change to uppercase if Uppercase is true
		Sprite character(TextureName, codepoint-32, CellSize); //codepoint-32 -> for bitmap texture
		character.Size = glm::vec2(FontSize, FontSize);
		character.Position = glm::vec2(x, y);
		character.IsBitmap = true;
		m_SB->Draw(character);
		x += LetterSpacing;
	}
	m_SB->End();
}


