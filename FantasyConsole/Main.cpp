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

	RectangleShape background(s_width, s_height, 0, 0);
	background.SetTexture("background");
	Sprite sprite("wall", glm::vec2(50, 0), glm::vec2(50, 50));
	Sprite sprite2("player", glm::vec2(100, 50), glm::vec2(50, 50));

	SpriteBatch sp;

	while (Window::IsOpen())
	{
		Renderer::Clear();

		Renderer::Draw(background);

		sp.Start();
		sp.Draw(sprite);
		sp.Draw(sprite2);
		sp.End();

		Window::Display();
	}
	Window::Terminate();
	return 0;
}

