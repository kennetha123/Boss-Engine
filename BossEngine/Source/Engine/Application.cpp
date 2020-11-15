#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace BossEngine
{
	BossEngine::Application::Application()
	{
	}

	BossEngine::Application::~Application()
	{

	}

	void Application::Run()
	{

		WindowResizeEvent e(1280, 720);
		BE_TRACE(e);

		while (true)
		{

		}
	}
}