#include "Input.h"

std::map<int, bool> Input::keys;
std::unordered_map<const char*, std::function<void(GLFWwindow*, unsigned int)>> Input::onCharacterListeners;
std::unordered_map<const char*, std::function<void(GLFWwindow*, int, int, int, int)>> Input::onKeyListeners;

bool Input::IsKeyPressed(int key) {
	return keys[key];
}
void Input::Init(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, character_callback);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);
}

void Input::RemoveEventListener(InputEvent event, const char* name) {
	switch (event)
	{
	case OnCharacterInput:
		onCharacterListeners.erase(name);
		break;
	case OnKeyInput:
		onKeyListeners.erase(name);
		break;
	default:
		break;
	}
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

 void Input::character_callback(GLFWwindow* window, unsigned int codepoint) {
	for (auto pair : onCharacterListeners) {
		pair.second(window, codepoint);
	}
}

 void Input::window_resize_callback(GLFWwindow* window, int width, int height) {
	 lcall(glViewport(0, 0, width, height));
 }
