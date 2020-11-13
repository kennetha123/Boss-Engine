#pragma once

#ifdef BE_PLATFORM_WINDOWS

extern BossEngine::Application* BossEngine::CreateApplication();

int main(int argc, char** argv)
{
	printf("Welcome!");
	auto app = BossEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif