#include <glm/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <array>

#include "RectangleShape.h"
#include "Variables.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Input.h"
#include "SpriteBatch.h"
#include "TextRenderer.h"
#include "PolygonShape.h"
#include "TextEditor.h"

using namespace std;

int main()
{
	Window::Create();

	rm::LoadTexture("Resources/Assets/background.png", "background");
	rm::LoadTexture("Resources/wall.jpg", "wall");
	rm::LoadTexture("Resources/Assets/Spaceships/01/Spaceship_01_GREEN.png", "player");
	rm::LoadTexture("Resources/01-generic.png", "sheet");
	rm::LoadTexture("Resources/ExportedFont.bmp", "font");

	RectangleShape background(s_width, s_height, 0, 0);
	background.SetTexture("background");

	PolygonShape poly(100, 4, 50, 50);
	poly.SetTexture("wall");
	poly.RemoveTexture();
	poly.SetColor(1.0, 1.0, 1.0, 1.0);
	poly.SetTexture("wall");

	TextRenderer text("font", glm::vec2(24, 24));
	TextEditor textEditor(text);
	//SpriteBatch sp;

	while (Window::IsOpen())
	{
		if (Input::GetKeyState(GLFW_KEY_D)) {
		}

		Window::Clear(0.5f, 0.5f, 1.0f, 1.0f);
		background.Draw();
		textEditor.Draw();
		Window::Display();
	}
	Window::Terminate();
	return 0;
}

