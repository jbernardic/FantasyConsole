#include <glm/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <iostream>

#include "Renderer.h"
#include "Variables.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Input.h"
#include "SpriteBatch.h"
#include <array>

using namespace std;
typedef ResourceManager rm;

int main()
{
	Window::Create();

	rm::LoadTexture("Resources/Assets/background.png", "background");
	rm::LoadTexture("Resources/wall.jpg", "wall");
	rm::LoadTexture("Resources/Assets/Spaceships/01/Spaceship_01_GREEN.png", "player");
	rm::LoadTexture("Resources/01-generic.png", "sheet");

	RectangleShape background(s_width, s_height, 0, 0);
	background.SetTexture("background");
	Sprite s("sheet", 4, glm::vec2(16.0, 16.0));
	s.Size = glm::vec2(100, 100);
	s.Position = glm::vec2(100, 0);
	Sprite a("wall");
	a.Size = glm::vec2(50, 50);

	SpriteBatch sp;

	while (Window::IsOpen())
	{

		if (Input::GetKeyState(GLFW_KEY_D)) {
			s.CellIndex++;
		}

		Renderer::Clear();


		sp.Start();
		sp.Draw(a);
		sp.Draw(s);
		sp.Draw(s);
		sp.End();

		Window::Display();
	}
	Window::Terminate();
	return 0;
}

