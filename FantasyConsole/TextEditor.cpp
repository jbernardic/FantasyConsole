#include "TextEditor.h"
#include "Input.h"
#include <numeric>

TextEditor::TextEditor(TextRenderer& textRenderer) : m_TextRenderer(textRenderer)
{
	m_Cursor.SetColor(1.0, 1.0, 1.0, 1.0);
	//on key press
	KeyInputCallback keyCallback = [&](GLFWwindow* window, int key, int scan, int action, int mode) {
		if (key == GLFW_KEY_BACKSPACE && !Text.empty() && action > 0 && !(CursorPosition.x == 0 && CursorPosition.y == 0)) { //if BACKSPACE pressed
			if (CursorPosition.x == 0 && CursorPosition.y > 0) {
				std::string s = Text[CursorPosition.y];
				Text.erase(Text.begin() + CursorPosition.y);
				CursorPosition = FindCursor(UINT16_MAX, CursorPosition.y-1);
				Text[CursorPosition.y] += s;
			}
			else {
				CursorPosition.x--;
				Text[CursorPosition.y].erase(CursorPosition.x, 1);
			}
		}
		else if (key == GLFW_KEY_ENTER && action > 0) { //if ENTER pressed
			std::string s = Text[CursorPosition.y].substr(CursorPosition.x);
			Text.insert(Text.begin() + CursorPosition.y+1, s);
			Text[CursorPosition.y] = Text[CursorPosition.y].substr(0, CursorPosition.x);
			CursorPosition.x = 0;
			CursorPosition.y++;
		}
		else if (key == GLFW_KEY_LEFT && action > 0) {
			if (CursorPosition.x <= 0 && CursorPosition.y > 0) {
				CursorPosition = FindCursor(UINT16_MAX, CursorPosition.y-1);
			}
			else CursorPosition = FindCursor(CursorPosition.x - 1, CursorPosition.y);
		}
		else if (key == GLFW_KEY_RIGHT && action > 0) {
			if (CursorPosition.x >= Text[CursorPosition.y].size() && CursorPosition.y < Text.size() - 1) {
				CursorPosition = FindCursor(0, CursorPosition.y + 1);
			}
			else CursorPosition = FindCursor(CursorPosition.x+1, CursorPosition.y);
		}
		else if (key == GLFW_KEY_UP && action > 0 && CursorPosition.y > 0) {
			CursorPosition = FindCursor(CursorPosition.x, CursorPosition.y-1);
		}
		else if (key == GLFW_KEY_DOWN && action > 0) {
			CursorPosition = FindCursor(CursorPosition.x, CursorPosition.y+1);
		}
	};
	//on character type
	CharacterInputCallback characterCallback = [&](GLFWwindow* window, unsigned int codepoint) {
		if (codepoint-32 < 224) { //if in character atlas
			if (codepoint >= 65 && codepoint <= 90) codepoint += 32; //change to lowercase for Lua interpreter
			Text[CursorPosition.y].insert(CursorPosition.x, 1, codepoint);
			CursorPosition.x++;
		}
	};
	Input::AddEventListener("TextEditorKey", keyCallback);
	Input::AddEventListener("TextEditorCharacter", characterCallback);
}

void TextEditor::Draw()
{
	m_Cursor.SetPosition(static_cast<float>(CursorPosition.x*m_TextRenderer.LetterSpacing), static_cast<float>(CursorPosition.y*m_TextRenderer.LineSpacing));
	m_Cursor.Draw();
	if (Text.empty()) return;
	m_TextRenderer.Draw(Position, GetJointText());
}

glm::vec2 TextEditor::FindCursor(int x, int y)
{
	if (y < 0) y = 0;
	if (x < 0) x = 0;

	if (y >= Text.size()) {
		y = Text.size() - 1;
	}
	if (x >= Text[y].size()) x = Text[y].size();
	return glm::vec2(x, y);
}

std::string TextEditor::GetJointText()
{
	std::string separator = "\n";
	std::string result = std::accumulate(Text.begin() + 1, Text.end(), Text[0],
		[&](const std::string& a, const std::string& b) {
		return a + separator + b;
	});
	return result;
}
