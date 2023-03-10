#pragma warning(disable:6385)
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
#include "SpriteEditor.h"

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

static std::unique_ptr<SpriteBatch> SB;
static std::unique_ptr<Texture> LuaTEX;

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
	Sprite s = Sprite::CreateRectangle(glm::vec2(x, y), glm::vec2(width, height), color);
	SB->Draw(s);
	return 0;
}

int lua_SPR(lua_State* L) {
	unsigned int sindex = lua_tonumber(L, 1);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	float width = lua_tonumber(L, 4);
	float height = lua_tonumber(L, 5);

	Sprite s(LuaTEX.get(), sindex, glm::vec2(16));
	s.Position = glm::vec2(x, y);
	if(width != 0 && height != 0) s.Size = glm::vec2(width, height);
	SB->Draw(s);
	return 0;
}

int lua_BTN(lua_State* L) {
	int key = lua_tonumber(L, 1);
	lua_pushboolean(L, Input::IsKeyPressed(key));
	return 1;
}

int main()
{
	Window::Create(s_width*2, s_height*2);
	rm::LoadTexture("Resources/ExportedFont.bmp", "font");

	LuaTEX = std::make_unique<Texture>(nullptr, 64, 64);

	TextRenderer text("font", glm::vec2(8, 8));
	text.Uppercase = true;
	TextEditor textEditor(text);
	textEditor.Position = glm::vec2(2, 16);
	RectangleShape navigation(0, 0, s_width, 12);
	navigation.SetColor(0.0f, 0.0f, 0.0f, 1.0f);

	SB = std::make_unique <SpriteBatch>();
	SpriteEditor::Palette palette{
		colors, glm::vec2(102, 128), glm::vec2(164, 18), 3, 16
	};
	SpriteEditor spriteEditor(glm::vec2(6, 18), glm::vec2(128), glm::uvec2(16, 16), palette, LuaTEX.get());
	spriteEditor.Active = false;

	LuaScript script;
	bool isGameRunning = false;
	unsigned int tab = 0;
	std::string tabNames[2] = { "CODE EDITOR", "SPRITE EDITOR"};
	Input::AddEventListener("KeyListener", [&](GLFWwindow*, int key, int scan, int action, int mods) {
		if (key == GLFW_KEY_F5 && action > 0) {
			if (!isGameRunning) {
				script.NewState();

				lua_register(script.GetState(), "cls", lua_CLS);
				lua_register(script.GetState(), "rect", lua_RECT);
				lua_register(script.GetState(), "btn", lua_BTN);
				lua_register(script.GetState(), "spr", lua_SPR);

				script.Run(textEditor.GetJointText());
				script.CallFunction("_init");
				isGameRunning = true;
			}
			else {
				script.Close();
				isGameRunning = false;
				textEditor.Active = false;
				spriteEditor.Active = false;
			}
		}
		else if (key == GLFW_KEY_F1 && action > 0) {
			tab = (tab + 1) % 2;
		}
	});
	while (Window::IsOpen())
	{
		if (!isGameRunning) {
			if (tab == 0) {
				textEditor.Active = true;
				spriteEditor.Active = false;
			}
			else {
				spriteEditor.Active = true;
				textEditor.Active = false;
			}
			glm::vec4 color = colors[5] / 255.0f;
			Window::Clear(color.r, color.g, color.b, color.a);
			
			switch (tab) {
			case 0: //code editor
				textEditor.Draw();
				break;
			case 1: //sprite editor
				SB->Begin();
				spriteEditor.Draw(*SB);
				SB->End();
				break;
			}

			navigation.Draw();
			navigation.Translate(glm::vec2(0, s_height-12));
			navigation.Draw();
			navigation.Translate(glm::vec2(0, -(s_height-12)));

			text.Draw(glm::vec2(2, 3), "KONZOLA");
			text.Draw(glm::vec2(s_width-50, 3), "F5-RUN");
			int digits = static_cast<int>(log10(textEditor.CharacterCount));
			text.Draw(glm::vec2(s_width - 58 - digits*8, s_height-9), std::to_string(textEditor.CharacterCount) + "/65536");
			text.Draw(glm::vec2(2, s_height - 9), "<F1> " + tabNames[tab]);
		}
		else {
			textEditor.Active = false;
			spriteEditor.Active = false;
			script.CallFunction("_update");
			Window::Clear(0.0, 0.0, 0.0, 1.0);
			SB->Begin();
			script.CallFunction("_draw");
			SB->End();
		}
		Window::Display();
	}
	Window::Terminate();
	return 0;
}

