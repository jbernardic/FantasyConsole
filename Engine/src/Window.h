#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	static void Create();
	static bool IsOpen();
	static void Display();
	static void Terminate();
	static void Clear(float r, float g, float b, float a);
	static GLFWwindow* Get() { return window; }

private:
	static GLFWwindow* window;
};

