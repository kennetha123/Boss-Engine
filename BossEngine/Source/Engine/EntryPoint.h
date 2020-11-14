#pragma once

#ifdef BE_PLATFORM_WINDOWS

// entry point of the Engine.
int main(int argc, char** argv)
{
	int wew = 5;
	
	BossEngine::Log::Init();
	BE_CORE_ERROR("Init Log!");
	BE_INFO("Init Log! {0}", wew);

	auto app = BossEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif