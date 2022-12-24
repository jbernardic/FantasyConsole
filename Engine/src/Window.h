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

private:
	static GLFWwindow* window;
};

