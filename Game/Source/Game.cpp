#include <BossEngine.h>

class ExampleLayer : public BossEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (BossEngine::Input::IsKeyPressed(BE_KEY_TAB))
		{
			BE_TRACE("Key Tab pressed!");
		}
	}

	void OnEvent(BossEngine::Event& event) override
	{
		//BE_TRACE("{0}", event);
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
		PushOverlay(new BossEngine::ImGuiLayer());
	}

	~Game()
	{

	}
};

BossEngine::Application* BossEngine::CreateApplication()
{
	return new Game();
}