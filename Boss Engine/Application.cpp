#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void InputProcess(GLFWwindow* window);

int main()
{
#pragma region  Initialize
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Boss Engine v.0.0.1a", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "GLFW_INITIALIZATION::FAILED!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD_INITIALIZATION::FAILED!" << std::endl;
		return -1;
	}
#pragma endregion

#pragma region Window Loop
	//--------------Window Loop------------------//
	while (!glfwWindowShouldClose(window))
	{
		InputProcess(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.2f, 0.4f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

	glfwTerminate();
	return 0;
}

#pragma region Function
//----------------Function-------------------------//
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void InputProcess(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
#pragma endregion
