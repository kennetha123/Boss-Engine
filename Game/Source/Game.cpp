#include <BossEngine.h>

class ExampleLayer : public BossEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		// Check if player pressing Tab
		if (BossEngine::Input::IsKeyPressed(BE_KEY_TAB))
		{
			BE_TRACE("Key Tab pressed!");
		}
	}

	void OnEvent(BossEngine::Event& event) override
	{
		//BE_TRACE("{0}", event);

		//Check player typing
		if (event.GetEventType() == BossEngine::EventType::KeyPressed)
		{
			BossEngine::KeyPressedEvent& e = (BossEngine::KeyPressedEvent&)event;
			BE_TRACE("{0}", (char)e.GetKeyCode());
		}
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