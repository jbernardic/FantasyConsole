#include "TextEditor.h"
#include "Input.h"

TextEditor::TextEditor(TextRenderer& textRenderer) : m_TextRenderer(textRenderer)
{
	m_Cursor.SetColor(1.0, 1.0, 1.0, 1.0);
	//on key press
	KeyInputCallback keyCallback = [&](GLFWwindow* window, int key, int scan, int action, int mode) {
		if (key == 259 && !Text.empty() && action > 0) { //if BACKSPACE pressed
			Text.pop_back();
			CursorPosition--;
		}
		else if (key == 257 && action > 0) { //if ENTER pressed
			Text.push_back('\n');
			CursorPosition++;
		}
	};
	//on character type
	CharacterInputCallback characterCallback = [&](GLFWwindow* window, unsigned int codepoint) {
		if (codepoint-32 < 224) { //if in character atlas
			Text.push_back(codepoint);
			CursorPosition++;
		}
	};
	Input::AddEventListener("TextEditorKey", keyCallback);
	Input::AddEventListener("TextEditorCharacter", characterCallback);
}

void TextEditor::Draw()
{
	//find cursor position
	unsigned int cursorX = 0;
	unsigned int cursorY = 0;
	for (int i = CursorPosition; i >= 0; i--) {
		if (Text[i] == '\n') {
			cursorY+=m_TextRenderer.LineSpacing;
		}
		else if(cursorY == 0){
			if (Text[i] == ' ') cursorX += m_TextRenderer.SpaceSpacing;
			else cursorX += m_TextRenderer.LetterSpacing;
		}
	}

	m_Cursor.SetPosition(cursorX, cursorY);
	m_Cursor.Draw();
	m_TextRenderer.Draw(Position, Text);
}
