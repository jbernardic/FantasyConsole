#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include "ErrorHandler.h"

using CharacterInputCallback = std::function<void(GLFWwindow*, unsigned int)>;
using KeyInputCallback = std::function<void(GLFWwindow*, int, int, int, int)>;
using MouseButtonCallback = std::function<void(GLFWwindow*, int button, int action, int mods)>;
using CursorPositionCallback = std::function<void(GLFWwindow* window, double xpos, double ypos)>;

enum InputEvent {
	CharacterInput, KeyInput, MouseButtonInput, CursorPositionInput
};
class Input {
public:
	static void Init(GLFWwindow* window);
	static bool IsKeyPressed(int key);
	static glm::dvec2 GetCursorPosition() { return CursorPosition; };
	static void RemoveEventListener(InputEvent, const char* name);

	static void AddEventListener(const char* name, CharacterInputCallback func) {
		CharacterListeners[name] = func;
	}
	static void AddEventListener(const char* name, KeyInputCallback func) {
		KeyListeners[name] = func;
	}
	static void AddEventListener(const char* name, MouseButtonCallback func) {
		MouseButtonListeners[name] = func;
	}
	static void AddEventListener(const char* name, CursorPositionCallback func) {
		CursorPositionListener[name] = func;
	}
private:
	static glm::dvec2 CursorPosition;
	static std::map<int, bool> keys;
	static std::unordered_map<const char*, CharacterInputCallback> CharacterListeners;
	static std::unordered_map<const char*, KeyInputCallback> KeyListeners;
	static std::unordered_map<const char*, MouseButtonCallback> MouseButtonListeners;
	static std::unordered_map<const char*, CursorPositionCallback> CursorPositionListener;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void character_callback(GLFWwindow* window, unsigned int codepoint);
	static void window_resize_callback(GLFWwindow* window, int width, int height);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
