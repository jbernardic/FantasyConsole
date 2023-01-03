#pragma once
#include <glad/glad.h>
#include "Input.h"

class Window
{
public:
	static void Create(int width, int height);
	static bool IsOpen();
	static void Display();
	static void Terminate();
	static void Clear(float r, float g, float b, float a);
	static GLFWwindow* Get() { return window; }
	static glm::ivec2 Size;
private:
	static GLFWwindow* window;
};

