#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <map>

class Input {
public:
	static void SetCallbacks(GLFWwindow* window);
	static bool GetKeyState(int key);
	static void AddCharacterListener();
	static void OnKeyPressed(void (*func)(GLFWwindow* window, int key, int scancode, int action, int mods));
private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_resize_callback(GLFWwindow* window, int width, int height);
	static std::map<int, bool> Keys;
};