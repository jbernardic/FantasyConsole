#include "Input.h"

std::map<int, bool> Input::keys;
std::unordered_map<const char*, std::function<void(GLFWwindow*, unsigned int)>> Input::onCharacterListeners;
std::unordered_map<const char*, std::function<void(GLFWwindow*, int, int, int, int)>> Input::onKeyListeners;

bool Input::GetKeyState(int key) {
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