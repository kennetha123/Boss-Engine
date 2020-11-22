#include <BossEngine.h>

class ExampleLayer : public BossEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		BE_INFO("ExampleLayer::Updated");
	}

	void OnEvent(BossEngine::Event& event) override
	{
		BE_TRACE("{0}", event);
	}
};

class Game : public BossEngine::Application
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
	}

	~Game()
	{

	}
};

BossEngine::Application* BossEngine::CreateApplication()
{
	return new Game();
}