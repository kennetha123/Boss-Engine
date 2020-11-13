#include <BossEngine.h>

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