#include <BossEngine.h>

using BossEngine::Application;

class Game : public BossEngine::Application
{
public:
	Game()
	{

	}

	~Game()
	{

	}
};

BossEngine::Application* BossEngine::CreateApplication()
{
	return new Game();
}