#include "Input.h"
#include "ErrorHandler.h"

std::map<int, bool> Input::keys;

bool Input::GetKeyState(int key) {
	return keys[key];
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		Input::keys[key] = true;
	}
	if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}

void Input::window_resize_callback(GLFWwindow* window, int width, int height) {
	lcall(glViewport(0, 0, width, height));
}

void Input::SetCallbacks(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, Input::window_resize_callback);
}
