#include "Window.h"

GLFWwindow* Window::window = nullptr;
glm::ivec2 Window::Size(0.0);

void Window::Create(int width, int height)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	/* Create a windowed mode window and its OpenGL context */
	Size = glm::ivec2(width, height);
	window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGL();

	Input::Init(window);
	Window::window = window;
}

bool Window::IsOpen() {
	return !glfwWindowShouldClose(Window::window);
}

void Window::Display() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::Terminate() {
	glfwTerminate();
}

void Window::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
