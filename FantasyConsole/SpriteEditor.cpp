#include "SpriteEditor.h"
#include "Input.h"
#include "Window.h"
#include "Variables.h"

SpriteEditor::SpriteEditor(glm::vec2 position, glm::vec2 size, glm::uvec2 gridSize, Palette Palette, Texture* texture) : Position(position), m_Texture(texture), m_GridSize(gridSize), Size(size), m_Pallete(Palette)
{
	unsigned int swidth = m_GridSize.x;
	unsigned int sheight = m_GridSize.y;

	for (unsigned int i = 0; i < 64; i++) {
		for (unsigned int j = 0; j < 64; j++) {
			m_TextureData[i][j] = { 0, 0, 0, 255 };
		}
	}
	m_Texture->SetData(m_TextureData);

	Input::AddEventListener("SpriteEditorCursorPosition", [&](GLFWwindow* window, double xpos, double ypos) {
		if (!Active || m_DrawingColor < 0) return;
		DrawPixel(Input::GetCursorPosition(), PickedColors[m_DrawingColor % 2]);
	});

	Input::AddEventListener("SpriteEditorMouseClick", [&](GLFWwindow* window, int button, int action, int mods) {
		if (!Active || button > 1) return;
		if (action > 0) {
			m_DrawingColor = button;
			DrawPixel(Input::GetCursorPosition(), PickedColors[m_DrawingColor]);
			glm::vec4 color = PickColor(Input::GetCursorPosition()) / glm::vec4(255);
			if(color.a > 0) PickedColors[button] = PickColor(Input::GetCursorPosition()) / glm::vec4(255);
		}
		else m_DrawingColor = -1;
	});

	Input::AddEventListener("SpriteEditorCharacterInput", [&](GLFWwindow* window, int codepoint) {
		if (!Active) return;
	});
}
SpriteEditor::~SpriteEditor()
{
	Input::RemoveEventListener(MouseButtonInput, "SpriteEditorMouseClick");
	Input::RemoveEventListener(CursorPositionInput, "SpriteEditorCursorPosition");
	Input::RemoveEventListener(CharacterInput, "SpriteEditorCharacterInput");
}

void SpriteEditor::Draw(SpriteBatch& sb)
{
	glm::vec4 bgColor = m_Pallete.Colors[13] / glm::vec4(255);
	glm::vec4 bgColor2 = m_Pallete.Colors[1] / glm::vec4(255);
	Sprite background1 = Sprite::CreateRectangle(glm::vec2(), glm::vec2(s_width, s_height - s_height * 0.3), bgColor);
	Sprite background2 = Sprite::CreateRectangle(glm::vec2(0, s_height - s_height * 0.3), glm::vec2(s_width, s_height * 0.3), bgColor2);
	sb.Draw(background1);
	sb.Draw(background2);
	Sprite paletteBackground = Sprite::CreateRectangle(m_Pallete.Position, m_Pallete.Size, m_Pallete.Colors[0] / glm::vec4(255));
	sb.Draw(paletteBackground);

	Sprite canvas(m_Texture, 0, glm::vec2(16));
	canvas.Size = Size;
	canvas.Position = Position;
	sb.Draw(canvas);

	for (unsigned int i = 0; i < m_Pallete.ColorCount; i++) {
		glm::vec2 psize = m_Pallete.Size;
		glm::vec2 colorSize = glm::vec2(psize.x/ static_cast<float>(m_Pallete.ColumnCount), psize.y/ceil(m_Pallete.ColorCount/static_cast<float>(m_Pallete.ColumnCount)));
		float x = (i % m_Pallete.ColumnCount) * colorSize.x;
		float y = (i / m_Pallete.ColumnCount) * colorSize.y;
		glm::vec2 colorPos = m_Pallete.Position + glm::vec2(x, y);
		Sprite colorSprite = Sprite::CreateRectangle(colorPos, colorSize, m_Pallete.Colors[i]/glm::vec4(255));
		sb.Draw(colorSprite);
	}
	for (unsigned int i = 0; i < 2; i++) {
		glm::vec2 size = glm::vec2(32, 32);
		Sprite colorSprite = Sprite::CreateRectangle(m_Pallete.Position + glm::vec2(m_Pallete.Size.x + 15, 0) + glm::vec2((size.x+3)*i, 0), size, PickedColors[i]);
		sb.Draw(colorSprite);
	}
}

void SpriteEditor::DrawPixel(glm::dvec2 position, glm::vec4 color)
{
	glm::vec2 m = Window::Size / glm::ivec2(s_width, s_height);
	glm::dvec2 cpos = position;
	cpos = cpos / glm::dvec2(m);

	bool inX = cpos.x > Position.x && cpos.x < Position.x + Size.x;
	bool inY = cpos.y > Position.y && cpos.y < Position.y + Size.y;
	if (inX && inY) {
		unsigned int gridX = (cpos.x - Position.x) / (Size.x / m_GridSize.x);
		unsigned int gridY = (cpos.y - Position.y) / (Size.y / m_GridSize.y);
		color *= glm::vec4(255);
		m_TextureData[gridY][gridX] = { static_cast<unsigned char>(color.r), static_cast<unsigned char>(color.g), static_cast<unsigned char>(color.b), static_cast<unsigned char>(color.a) };
		m_Texture->SetData(m_TextureData);
	}
}

glm::vec4 SpriteEditor::PickColor(glm::dvec2 position)
{
	glm::vec2 m = Window::Size / glm::ivec2(s_width, s_height);
	glm::dvec2 cpos = position;
	cpos = cpos / glm::dvec2(m);

	bool inX = cpos.x > m_Pallete.Position.x && cpos.x < m_Pallete.Position.x + m_Pallete.Size.x;
	bool inY = cpos.y > m_Pallete.Position.y && cpos.y < m_Pallete.Position.y + m_Pallete.Size.y;
	
	if (inX && inY) {
		unsigned int gridX = (cpos.x - m_Pallete.Position.x) / (m_Pallete.Size.x / m_Pallete.ColumnCount);
		unsigned int gridY = (cpos.y - m_Pallete.Position.y) / (m_Pallete.Size.y / ceil(m_Pallete.ColorCount / static_cast<float>(m_Pallete.ColumnCount)));
		unsigned int i = gridY * m_Pallete.ColumnCount + gridX;
		return m_Pallete.Colors[i];
	}
	return glm::vec4();
}