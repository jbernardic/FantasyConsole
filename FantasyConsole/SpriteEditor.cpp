#include "SpriteEditor.h"
#include "Input.h"
#include "Window.h"
#include "Variables.h"

SpriteEditor::SpriteEditor(glm::vec2 position, glm::vec2 size, unsigned int swidth, unsigned int sheight) : Position(position), m_GridSize(swidth, sheight), Size(size)
{
	m_Grid = (Sprite*)calloc(swidth * sheight, sizeof(Sprite));
	if (m_Grid == NULL) return;
	for (unsigned int i = 0; i < swidth * sheight; i++) {
		m_Grid[i] = Sprite::CreateRectangle(size/glm::vec2(swidth, sheight), glm::vec4(0.0, 0.0, 0.0, 1.0));
	}

	Input::AddEventListener("SpriteEditorCursorPosition", [&](GLFWwindow* window, double xpos, double ypos) {
		if (!Active || !m_Drawing) return;
		DrawPixel(Input::GetCursorPosition());
	});

	Input::AddEventListener("SpriteEditorMouseClick", [&](GLFWwindow* window, int button, int action, int mods) {
		if (!Active) return;
		if (action > 0) {
			m_Drawing = true;
			DrawPixel(Input::GetCursorPosition());
		}
		else m_Drawing = false;
	});
}

void SpriteEditor::Draw(SpriteBatch& sb)
{
	for (unsigned int i = 0; i < m_GridSize.x * m_GridSize.y; i++) {
		unsigned int x = (i % m_GridSize.x)*m_Grid[i].Size.x + Position.x;
		unsigned int y = (i / m_GridSize.x)* m_Grid[i].Size.y + Position.y;
		m_Grid[i].Position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
		sb.Draw(m_Grid[i]);
	}
}

void SpriteEditor::DrawPixel(glm::dvec2 position)
{
	glm::vec2 m = Window::Size / glm::ivec2(s_width, s_height);
	glm::dvec2 cpos = position;
	cpos = cpos / glm::dvec2(m);

	bool inX = cpos.x > Position.x && cpos.x < Position.x + Size.x;
	bool inY = cpos.y > Position.y && cpos.y < Position.y + Size.y;
	if (inX && inY) {
		unsigned int gridX = (cpos.x - Position.x) / (Size.x / m_GridSize.x);
		unsigned int gridY = (cpos.y - Position.y) / (Size.y / m_GridSize.y);
		unsigned int i = gridY * m_GridSize.x + gridX;
		m_Grid[i].Color = glm::vec4(1.0);
	}
}

SpriteEditor::~SpriteEditor()
{
	delete m_Grid;
	Input::RemoveEventListener(MouseButtonInput, "SpriteEditorMouseClick");
	Input::RemoveEventListener(CursorPositionInput, "SpriteEditorCursorPosition");
}
