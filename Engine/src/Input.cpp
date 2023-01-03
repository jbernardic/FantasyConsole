#include "Input.h"
#include "Window.h"

glm::dvec2 Input::CursorPosition(0.0);
std::map<int, bool> Input::keys;
std::unordered_map<const char*, CharacterInputCallback> Input::CharacterListeners;
std::unordered_map<const char*, KeyInputCallback> Input::KeyListeners;
std::unordered_map<const char*, MouseButtonCallback> Input::MouseButtonListeners;
std::unordered_map<const char*, CursorPositionCallback> Input::CursorPositionListener;

bool Input::IsKeyPressed(int key) {
	return keys[key];
}
void Input::Init(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, character_callback);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Input::RemoveEventListener(InputEvent event, const char* name) {
	switch (event)
	{
	case CharacterInput:
		CharacterListeners.erase(name);
		break;
	case KeyInput:
		KeyListeners.erase(name);
		break;
	case MouseButtonInput:
		MouseButtonListeners.erase(name);
	default:
		break;
	}
}

void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	CursorPosition = glm::dvec2(xpos, ypos);
	for (auto pair : CursorPositionListener) {
		pair.second(window, xpos, ypos);
	}
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	for (auto pair : MouseButtonListeners) {
		pair.second(window, button, action, mods);
	}
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		keys[key] = true;
	}
	if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
	for (auto pair : KeyListeners) {
		pair.second(window, key, scancode, action, mods);
	}
}

 void Input::character_callback(GLFWwindow* window, unsigned int codepoint) {
	for (auto pair : CharacterListeners) {
		pair.second(window, codepoint);
	}
}

 void Input::window_resize_callback(GLFWwindow* window, int width, int height) {
	 Window::Size = glm::ivec2(width, height);
	 lcall(glViewport(0, 0, width, height));
 }
