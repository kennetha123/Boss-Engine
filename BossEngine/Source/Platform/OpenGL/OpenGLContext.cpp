#include "bepch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace BossEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BE_CORE_ASSERT(status, "Failed to Initialize Glad!");

	}

	void OpenGLContext::SwapBuffers()
	{
		glBegin(GL_TRIANGLES);

		glEnd();

		glfwSwapBuffers(m_WindowHandle);
	}
}