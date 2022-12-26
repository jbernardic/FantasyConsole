#include "Text.h"
#include "Input.h"

std::unique_ptr<SpriteBatch> Text::SB;
const char* Text::TextureName;
glm::vec2 Text::CellSize;

static unsigned int val = 0;

static std::vector<Sprite> sprites;

static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Sprite s = Sprite(Text::TextureName, key, Text::CellSize);
	s.Position = glm::vec2(50, 50);
	sprites.push_back(s);
}

void Text::Init(const char* texture, glm::vec2 cellSize) {
	TextureName = texture;
	CellSize = cellSize;
	SB = std::make_unique<SpriteBatch>();
	Input::OnKeyPressed(onKeyPressed);
}
void Text::Draw(const char* text)
{

	//BROKEN SB
	SB->Begin();
	Sprite s("sheet", 4, glm::vec2(16.0, 16.0));
	s.Size = glm::vec2(100, 100);
	s.Position = glm::vec2(100, 0);
	Sprite a("wall");
	a.Size = glm::vec2(50, 50);
	SB->Draw(s);
	SB->Draw(a);
	SB->End();
}
