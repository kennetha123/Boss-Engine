#include <BossEngine.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public BossEngine::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_ObjectPosition(0.0f)

	{
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// RENDERING /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

		// NOTE : To create an image, we need 3 things to set up :
		// Vertex Array (VAO) , Vertex Buffer (VBO) , and Element Buffer (EBO)
		// So we will create VB first, then set up the VA and combine it on EB.

//////////////////////////////////////////////////////////////////////////////////////////
						//WILL BE DELETED LATER ON//
//////////////////////////////////////////////////////////////////////////////////////////
		// Verts & Indices

		// Vertices data, this will be setup in DCC (digital content creator)
		float vertices[4 * 7] =
		{
			// Position				// Color
		   -0.75f, -0.75f, 0.0f,	 1.0f,	0.0f, 0.0f, 1.0f,	// bottom left
			0.75f, -0.75f, 0.0f,	 0.0f,  0.0f, 1.0f, 1.0f,	// bottom right
			0.75f,  0.75f, 0.0f,	 0.0f,  1.0f, 0.0f, 1.0f,	// top right
		   -0.75f,  0.75f, 0.0f,	 0.0f,  0.0f, 1.0f, 1.0f,	// top left

		};

		// Create Indices data. This should be in DCC later on.
		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

		//////////////////////////////////////////////////////////////////////////////////////////
				// Vertex Shader and Fragment Shader.

		std::string vertexSource = R"(
			#version 330
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}		
		)";


		std::string fragmentSource = R"(
			#version 330
			
			layout(location = 0) out vec4 color;
			in vec4 v_Color;
				
			void main()
			{
				color = v_Color;
			}		
		)";
		//////////////////////////////////////////////////////////////////////////////////////////

				// Create Vertex Array
		m_VertexArray.reset(BossEngine::VertexArray::Create());

		// Create Vertex Buffer (need vertices data)
		m_VertexBuffer.reset(BossEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		// Create Buffer Layout so we can transform vertices data
		// into shader data.
		BossEngine::BufferLayout layout =
		{
			{ BossEngine::ShaderDataType::Float3, "a_Position" },
			{ BossEngine::ShaderDataType::Float4, "a_Color" }
		};

		// Set the layout into our Vertex Buffer.
		m_VertexBuffer->SetLayout(layout);

		// Add Vertex Buffer that has Layout into Vertex Array.
		// Make sure the Vertex Buffer already had a layout.
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Set ( Index Buffer / Element Buffer ) with indices.
		m_IndexBuffer.reset(BossEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		// Vertex Array set the IBO / EBO.
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		// Set Vertex and Fragment Shader.
		m_Shader.reset(new BossEngine::Shader(vertexSource, fragmentSource));

		//////////////////////////////////////////////////////////////////////////////////////////

	}

	void OnUpdate(BossEngine::DeltaTime deltaTime) override
	{
		BE_TRACE("Delta time : {0}s / {1}ms", deltaTime.GetSeconds(), deltaTime.GetMilliSeconds());

		///////////////////////////CAMERA INPUT////////////////////////////////
		if (BossEngine::Input::IsKeyPressed(BE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraPosSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraPosSpeed * deltaTime;
		
		if (BossEngine::Input::IsKeyPressed(BE_KEY_UP))
			m_CameraPosition.y += m_CameraPosSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraPosSpeed * deltaTime;

		if (BossEngine::Input::IsKeyPressed(BE_KEY_Q))
			m_CameraRotation -= m_CameraRotSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_E))
			m_CameraRotation += m_CameraRotSpeed * deltaTime;

		///////////////////////////OBJECT INPUT////////////////////////////////
		if (BossEngine::Input::IsKeyPressed(BE_KEY_A))
			m_ObjectPosition.x -= m_ObjectPosSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_D))
			m_ObjectPosition.x += m_ObjectPosSpeed * deltaTime;

		if (BossEngine::Input::IsKeyPressed(BE_KEY_W))
			m_ObjectPosition.y += m_ObjectPosSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_S))
			m_ObjectPosition.y -= m_ObjectPosSpeed * deltaTime;

		//if (BossEngine::Input::IsKeyPressed(BE_KEY_R))
		//	m_CameraRotation -= m_CameraRotSpeed * deltaTime;
		//else if (BossEngine::Input::IsKeyPressed(BE_KEY_T))
		//	m_CameraRotation += m_CameraRotSpeed * deltaTime;

		// Rendering
		BossEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		BossEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		BossEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ObjectPosition);
		
		BossEngine::Renderer::Submit(m_Shader, m_VertexArray, transform);
		
		BossEngine::Renderer::EndScene();
	}

	void OnEvent(BossEngine::Event& event) override
	{

	}

private:
	////////////////CAMERA///////////////////////////////////
	BossEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;

	float m_CameraPosSpeed = 1.0f;
	float m_CameraRotSpeed = 180.0f;

	////////////////OBJECT///////////////////////////////////
	std::shared_ptr<BossEngine::Shader> m_Shader;
	std::shared_ptr<BossEngine::VertexArray> m_VertexArray;
	std::shared_ptr<BossEngine::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<BossEngine::IndexBuffer> m_IndexBuffer;

	glm::vec3 m_ObjectPosition;
	float m_ObjectPosSpeed = 1.0f;

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