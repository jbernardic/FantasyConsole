#include <glm/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <unordered_map>

#include "RectangleShape.h"
#include "Variables.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Input.h"
#include "SpriteBatch.h"
#include "TextRenderer.h"
#include "PolygonShape.h"
#include "TextEditor.h"
#include "LuaScript.h"
#include "ShapeRenderer.h"

using namespace std;

static glm::vec4 colors[16] = {
	glm::vec4(0, 0, 0, 255),
	glm::vec4(29, 43, 83, 255),
	glm::vec4(126, 37, 83, 255),
	glm::vec4(0, 135, 81, 255),
	glm::vec4(171, 82, 54, 255),
	glm::vec4(95, 87, 79, 255),
	glm::vec4(194, 195, 199, 255),
	glm::vec4(255, 241, 232, 255),
	glm::vec4(255, 0, 77, 255),
	glm::vec4(255, 163, 0, 255),
	glm::vec4(255, 236, 39, 255),
	glm::vec4(0, 228, 54, 255),
	glm::vec4(41, 173, 255, 255),
	glm::vec4(131, 118, 156, 255),
	glm::vec4(255, 119, 168, 255),
	glm::vec4(255, 204, 170, 255)
};

static ShapeRenderer LuaShapes;

int lua_CLS(lua_State* L) {
	unsigned int c = lua_tonumber(L, 1);
	glm::vec4 color = colors[c] / (float)255;
	Window::Clear(color.r, color.g, color.b, color.a);
	return 0;
}

int lua_RECT(lua_State* L) {
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float width = lua_tonumber(L, 3);
	float height = lua_tonumber(L, 4);
	unsigned int c = lua_tonumber(L, 5);
	glm::vec4 color = colors[c] / (float)255;
	LuaShapes.DrawRectangle(glm::vec4(x, y, width, height), color);
	return 0;
}

int lua_BTN(lua_State* L) {
	int key = lua_tonumber(L, 1);
	lua_pushboolean(L, Input::IsKeyPressed(key));
	return 1;
}

int main()
{
	Window::Create();
	rm::LoadTexture("Resources/ExportedFont.bmp", "font");

	TextRenderer text("font", glm::vec2(8, 8));
	text.Uppercase = true;
	TextEditor textEditor(text);
	textEditor.Position = glm::vec2(5, 20);
	RectangleShape navigation(0, 0, s_width, 15);
	navigation.SetColor(0.0f, 0.0f, 0.0f, 1.0f);

	LuaScript script;
	bool isGameRunning = false;

	Input::AddEventListener("KeyListener", [&](GLFWwindow*, int key, int scan, int action, int mods) {
		if (key == GLFW_KEY_F5 && action > 0) {
			if (!isGameRunning) {
				script.NewState();

				lua_register(script.GetState(), "cls", lua_CLS);
				lua_register(script.GetState(), "rect", lua_RECT);
				lua_register(script.GetState(), "btn", lua_BTN);

				script.Run(textEditor.GetJointText());
				script.CallFunction("_init");
				isGameRunning = true;
			}
			else {
				script.Close();
				isGameRunning = false;
				LuaShapes.Clear();
			}
		}
	});

	while (Window::IsOpen())
	{
		if (!isGameRunning) {
			glm::vec4 color = colors[5] / 255.0f;
			Window::Clear(color.r, color.g, color.b, color.a);
			textEditor.Draw();
			navigation.Draw();
		}
		else {
			Window::Clear(0.0, 0.0, 0.0, 1.0);
			script.CallFunction("_update");
			script.CallFunction("_draw");
			LuaShapes.Draw();
		}
		Window::Display();
	}
	Window::Terminate();
	return 0;
}

