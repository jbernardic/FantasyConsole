#include "TextEditor.h"
#include "Input.h"

TextEditor::TextEditor(TextRenderer& textRenderer) : m_TextRenderer(textRenderer)
{
	m_Cursor.SetColor(1.0, 1.0, 1.0, 1.0);
	//on key press
	KeyInputCallback keyCallback = [&](GLFWwindow* window, int key, int scan, int action, int mode) {
		if (key == GLFW_KEY_BACKSPACE && !Text.empty() && action > 0) { //if BACKSPACE pressed
			if (Text.back() == '\n') {
				CursorPosition = FindCursor(UINT16_MAX, CursorPosition.y-1);
			}
			else CursorPosition.x--;
			Text.pop_back();
		}
		else if (key == GLFW_KEY_ENTER && action > 0) { //if ENTER pressed
			Text.push_back('\n');
			CursorPosition.x = 0;
			CursorPosition.y++;
		}
		else if (key == GLFW_KEY_LEFT && action > 0) {
			unsigned int pos = FindCursorPosition(CursorPosition.x, CursorPosition.y);
			if (pos <= 0) return;
			if (Text[pos-1] == '\n') {
				CursorPosition = FindCursor(UINT16_MAX, CursorPosition.y-1);
			}
			else if(CursorPosition.x>0) CursorPosition.x--;
		}
		else if (key == GLFW_KEY_RIGHT && action > 0) {
			unsigned int pos = FindCursorPosition(CursorPosition.x, CursorPosition.y);
			if (pos < Text.size() && Text[pos] == '\n') {
				CursorPosition.y++;
				CursorPosition.x = 0;
			}
			else if (pos < Text.size()) {
				CursorPosition.x++;
			}
		}
		else if (key == GLFW_KEY_UP && action > 0 && CursorPosition.y > 0) {
			CursorPosition = FindCursor(CursorPosition.x, CursorPosition.y-1);
		}
		else if (key == GLFW_KEY_DOWN && action > 0) {
			glm::vec2 cpos = FindCursor(CursorPosition.x, CursorPosition.y+1);
			if (cpos.y != CursorPosition.y) CursorPosition = cpos;
		}
	};
	//on character type
	CharacterInputCallback characterCallback = [&](GLFWwindow* window, unsigned int codepoint) {
		if (codepoint-32 < 224) { //if in character atlas
			Text.push_back(codepoint);
			if (codepoint == '\n') {
				CursorPosition.x = 0;
				CursorPosition.y++;
			}
			else CursorPosition.x++;
		}
	};
	Input::AddEventListener("TextEditorKey", keyCallback);
	Input::AddEventListener("TextEditorCharacter", characterCallback);
}

void TextEditor::Draw()
{
	m_Cursor.SetPosition(static_cast<float>(CursorPosition.x*m_TextRenderer.LetterSpacing), static_cast<float>(CursorPosition.y*m_TextRenderer.LineSpacing));
	m_Cursor.Draw();
	m_TextRenderer.Draw(Position, Text);
}

unsigned int TextEditor::FindCursorPosition(unsigned int x, unsigned int y)
{
	for (int i = 0; i < Text.size(); i++) {
		if (x == 0 && y == 0) {
			return i;
		}
		if (Text[i] == '\n') {
			if (y == 0) return i;
			y--;
			continue;
		}
		if(y == 0) x--;
	}
	return Text.size();
}

glm::vec2 TextEditor::FindCursor(unsigned int cursorX, unsigned int cursorY)
{
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int pos = FindCursorPosition(cursorX, cursorY);
	for (int i = 0; i < pos; i++) {
		if (Text[i] == '\n') {
			y++;
			x = 0;
		}
		else x++;
	}
	return glm::vec2(x, y);
}