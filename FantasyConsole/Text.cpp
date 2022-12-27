#include "Text.h"
#include "Input.h"

std::unique_ptr<SpriteBatch> Text::SB;
const char* Text::TextureName;
glm::vec2 Text::CellSize;

static unsigned int val = 0;

static std::vector<Sprite> sprites;
static int prevKey = 0;
static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Sprite s = Sprite(Text::TextureName, key, Text::CellSize);
	if(key != prevKey) sprites.push_back(s);
	prevKey = key;
}

void Text::Init(const char* texture, glm::vec2 cellSize) {
	TextureName = texture;
	CellSize = cellSize;
	SB = std::make_unique<SpriteBatch>();
	Input::OnKeyPressed(onKeyPressed);
}
void Text::Draw(const char* text)
{
	SB->Begin();
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].Position = glm::vec2(24 * i, 0);
		sprites[i].IsBitmap = true;
		SB->Draw(sprites[i]);
	}
	SB->End();
}
