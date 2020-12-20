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

		BE_CORE_INFO("OpenGL Renderer Information :");
		BE_CORE_INFO("Vendor   : {0}", glGetString(GL_VENDOR));
		BE_CORE_INFO("Renderer : {0}", glGetString(GL_RENDERER));
		BE_CORE_INFO("Version  : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glBegin(GL_TRIANGLES);

		glEnd();

		glfwSwapBuffers(m_WindowHandle);
	}
}