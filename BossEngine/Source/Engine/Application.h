#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace BossEngine
{
	class BE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}
