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
		Sprite character(TextureName, text[i]-32, CellSize);
		character.Size = glm::vec2(FontSize, FontSize);
		character.Position = glm::vec2(x, y);
		character.IsBitmap = true;
		m_SB->Draw(character);

		if (character.CellIndex == 0) x += SpaceSpacing;
		else x += LetterSpacing;
	}
	m_SB->End();
}

