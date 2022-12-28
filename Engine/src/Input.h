#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include "ErrorHandler.h"

using CharacterInputCallback = std::function<void(GLFWwindow*, unsigned int)>;
using KeyInputCallback = std::function<void(GLFWwindow*, int, int, int, int)>;

enum InputEvent {
	OnCharacterInput, OnKeyInput
};
class Input {
public:
	static void Init(GLFWwindow* window);
	static bool GetKeyState(int key);
	static void RemoveEventListener(InputEvent, const char* name);

	static void AddEventListener(const char* name, CharacterInputCallback func) {
		onCharacterListeners[name] = func;
	}
	static void AddEventListener(const char* name, KeyInputCallback func) {
		onKeyListeners[name] = func;
	}
private:
	static std::map<int, bool> keys;
	static std::unordered_map<const char*, CharacterInputCallback> onCharacterListeners;
	static std::unordered_map<const char*, KeyInputCallback> onKeyListeners;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
		for (auto pair : onKeyListeners) {
			pair.second(window, key, scancode, action, mods);
		}
	}
	static void character_callback(GLFWwindow* window, unsigned int codepoint) {
		for (auto pair : onCharacterListeners) {
			pair.second(window, codepoint);
		}
	}
	static void window_resize_callback(GLFWwindow* window, int width, int height) {
		lcall(glViewport(0, 0, width, height));
	}
};
