#include "Text.h"
#include "Input.h"
#include <Window.h>
#include "RectangleShape.h"

std::unique_ptr<SpriteBatch> Text::SB;
const char* Text::TextureName;
glm::vec2 Text::CellSize;

unsigned int FontSize = 16;
unsigned int SpaceSpacing = 10;
unsigned int LineSpacing = 16+4;
unsigned int LetterSpacing = 16-2;

std::vector<Sprite> characters;
std::unique_ptr<RectangleShape> cursor;
void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == 259 && !characters.empty() && action > 0) { //delete char

		if (characters.back().CellIndex != 0) cursor->SetPosition(cursor->GetPosition().x - LetterSpacing, cursor->GetPosition().y);
		else cursor->SetPosition(cursor->GetPosition().x - SpaceSpacing, cursor->GetPosition().y);

		characters.pop_back();
	}
	else if (key == 257 && action > 0) { //if ENTER pressed
		Sprite s = Sprite(Text::TextureName, -1, Text::CellSize);
		characters.push_back(s);
	}
}
void onCharacter(GLFWwindow* window, unsigned int codepoint) { //add char
	codepoint -= 32;
	if (codepoint < 224) { //if in character atlas
		Sprite s = Sprite(Text::TextureName, codepoint, Text::CellSize);
		s.Size = glm::vec2(FontSize, FontSize);
		characters.push_back(s);
		//Space has different spacing
		if(codepoint != 0) cursor->SetPosition(cursor->GetPosition().x + LetterSpacing, cursor->GetPosition().y);
		else cursor->SetPosition(cursor->GetPosition().x + SpaceSpacing, cursor->GetPosition().y);
	}
}

void Text::Init(const char* texture, glm::vec2 cellSize) {
	TextureName = texture;
	CellSize = cellSize;
	SB = std::make_unique<SpriteBatch>();
	glfwSetCharCallback(Window::Get(), onCharacter);
	glfwSetKeyCallback(Window::Get(), onKey);
	cursor = std::make_unique<RectangleShape>(14, 16);
}
void Text::DrawInput(glm::vec2 position)
{
	if ((int)(glfwGetTime()*1.5) % 2) cursor->SetColor(0, 0, 0, 0);
	else cursor->SetColor(1, 1, 1, 1);

	SB->Begin();
	unsigned int y = 0;
	unsigned int x = 0;
	for (int i = 0; i < characters.size(); i++) {
		if (characters[i].CellIndex == (unsigned int)-1) {
			y+=LineSpacing;
			x = 0;
			continue;
		}

		characters[i].Position = glm::vec2(x, y);
		characters[i].IsBitmap = true;
		SB->Draw(characters[i]);

		if (characters[i].CellIndex == 0) x += SpaceSpacing;
		else x += LetterSpacing;
	}
	SB->End();
	cursor->Draw();
}
