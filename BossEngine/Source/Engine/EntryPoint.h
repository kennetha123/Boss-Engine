#pragma once

#ifdef BE_PLATFORM_WINDOWS

// entry point of the Engine.
int main(int argc, char** argv)
{	
	BossEngine::Log::Init();
	BE_CORE_ERROR("Init Log!");
	auto app = BossEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif