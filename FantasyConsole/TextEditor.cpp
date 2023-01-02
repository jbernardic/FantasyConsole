#include "TextEditor.h"
#include "Input.h"
#include <numeric>

TextEditor::TextEditor(TextRenderer& textRenderer) : m_TextRenderer(textRenderer)
{
	m_Cursor.SetColor(1.0, 1.0, 1.0, 1.0);
	//on key press
	KeyInputCallback keyCallback = [&](GLFWwindow* window, int key, int scan, int action, int mode) {
		if (action <= 0) return;
		if (key == GLFW_KEY_BACKSPACE && !Text.empty() && !(CursorPosition.x == 0 && CursorPosition.y == 0)) { //if BACKSPACE pressed
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
		else if (key == GLFW_KEY_ENTER) { //if ENTER pressed
			std::string s = Text[CursorPosition.y].substr(CursorPosition.x);
			Text.insert(Text.begin() + CursorPosition.y+1, s);
			Text[CursorPosition.y] = Text[CursorPosition.y].substr(0, CursorPosition.x);
			CursorPosition.x = 0;
			CursorPosition.y++;
		}
		else if (key == GLFW_KEY_LEFT) {
			if (CursorPosition.x <= 0 && CursorPosition.y > 0) {
				CursorPosition = FindCursor(UINT16_MAX, CursorPosition.y-1);
			}
			else CursorPosition = FindCursor(CursorPosition.x - 1, CursorPosition.y);
		}
		else if (key == GLFW_KEY_RIGHT) {
			if (CursorPosition.x >= Text[CursorPosition.y].size() && CursorPosition.y < Text.size() - 1) {
				CursorPosition = FindCursor(0, CursorPosition.y + 1);
			}
			else CursorPosition = FindCursor(CursorPosition.x+1, CursorPosition.y);
		}
		else if (key == GLFW_KEY_UP && CursorPosition.y > 0) {
			CursorPosition = FindCursor(m_PreferredCol, CursorPosition.y - 1);
		}
		else if (key == GLFW_KEY_DOWN) {
			CursorPosition = FindCursor(m_PreferredCol, CursorPosition.y + 1);
		}
		if (key != GLFW_KEY_UP && key != GLFW_KEY_DOWN) {
			m_PreferredCol = CursorPosition.x;
		}
	};
	//on character type
	CharacterInputCallback characterCallback = [&](GLFWwindow* window, unsigned int codepoint) {
		if (codepoint-32 < 224) { //if in character atlas
			if (textRenderer.Uppercase && codepoint >= 65 && codepoint <= 90) codepoint += 32; //change to lowercase for Lua interpreter
			Text[CursorPosition.y].insert(CursorPosition.x, 1, codepoint);
			CursorPosition.x++;
			m_PreferredCol = CursorPosition.x;
		}
	};
	Input::AddEventListener("TextEditorKey", keyCallback);
	Input::AddEventListener("TextEditorCharacter", characterCallback);
}

void TextEditor::Draw()
{
	m_Cursor.SetPosition(static_cast<float>(CursorPosition.x*m_TextRenderer.LetterSpacing+Position.x), 
		static_cast<float>(CursorPosition.y*m_TextRenderer.LineSpacing+Position.y  - (m_TextRenderer.LineSpacing-m_TextRenderer.FontSize)+0.5f));
	m_Cursor.Draw();
	std::string text = GetJointText();
	CharacterCount = text.length();
	m_TextRenderer.Draw(Position, text);
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
