#include <BossEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Renderer/Shader.h"
#include <iostream>
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
		float vertices[5 * 4] =
		{
			// Position				// Texture Coordinate
		   -0.75f, -0.75f, 0.0f,	0.0f, 0.0f,	// bottom left
			0.75f, -0.75f, 0.0f,	1.0f, 0.0f,	// bottom right
			0.75f,  0.75f, 0.0f,	1.0f, 1.0f,	// top right
		   -0.75f,  0.75f, 0.0f,	0.0f, 1.0f,	// top left

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

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}		
		)";


		//////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////DATA OBJECT////////////////////////////////////////////
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
			{ BossEngine::ShaderDataType::Float2, "a_TexCoord" }
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

		//////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////SQUARE OBJECT////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////

		// Set Vertex and Fragment Shader.
		m_ShaderObject = BossEngine::Shader::Create("GameObject", vertexSource, fragmentSource);

		//////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////TEXTURE OBJECT////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////

		// Load Shader Asset.
		auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

		// Load Texture Asset.
		m_Texture = BossEngine::Texture2D::Create("Assets/Texture/container.jpg");
		m_TextureOverlay = BossEngine::Texture2D::Create("Assets/Texture/awesomeface.png");

		// Binding the Shader and send information to glsl file.
		std::dynamic_pointer_cast<BossEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<BossEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

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

		if (BossEngine::Input::IsKeyPressed(BE_KEY_LEFT_CONTROL))
			m_CameraPosition.z -= m_CameraPosSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_LEFT_SHIFT))
			m_CameraPosition.z += m_CameraPosSpeed * deltaTime;

		///////////////////////////OBJECT INPUT////////////////////////////////

		if (BossEngine::Input::IsKeyPressed(BE_KEY_A))
			m_ObjectPosition.x -= m_ObjectPosSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_D))
			m_ObjectPosition.x += m_ObjectPosSpeed * deltaTime;

		if (BossEngine::Input::IsKeyPressed(BE_KEY_W))
			m_ObjectPosition.y += m_ObjectPosSpeed * deltaTime;
		else if (BossEngine::Input::IsKeyPressed(BE_KEY_S))
			m_ObjectPosition.y -= m_ObjectPosSpeed * deltaTime;

		///////////////////////////RENDERING///////////////////////////////////

		// Clear background
		BossEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		BossEngine::RenderCommand::Clear();

		// Set camera position and rotation
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		
		{
			// Start Rendering Camera view
			BossEngine::Renderer::BeginScene(m_Camera);

			// Set up scale variable to use for scaling object
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));


			// Here we binding color of m_ShaderObject
			std::dynamic_pointer_cast<BossEngine::OpenGLShader>(m_ShaderObject)->Bind();
			std::dynamic_pointer_cast<BossEngine::OpenGLShader>(m_ShaderObject)->UploadUniformFloat3("u_Color", m_ObjectColor);

			// Create 20 * 20 square
			for (int x = 0; x < 20; x++)
			{
				for (int y = 0; y < 20; y++)
				{
					glm::vec3 pos(x * 0.15f, y * 0.15f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

					BossEngine::Renderer::Submit(m_ShaderObject, m_VertexArray, transform);
				}

			}

			// Set transform of Texture position
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ObjectPosition);

			// Tell which shader we want to use, in this case 'Texture.glsl'
			auto textureShader = m_ShaderLibrary.Get("Texture");

			// Texture binding with shader and vertices
			m_Texture->Bind();
			BossEngine::Renderer::Submit(textureShader, m_VertexArray, transform);

			// Texture overlay binding with shader and vertices
			m_TextureOverlay->Bind();
			BossEngine::Renderer::Submit(textureShader, m_VertexArray, transform);

			BossEngine::Renderer::EndScene();
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Object Color", glm::value_ptr(m_ObjectColor));
		ImGui::End();
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

	BossEngine::Ref<BossEngine::Shader> m_ShaderObject;
	BossEngine::Ref<BossEngine::VertexArray> m_VertexArray;
	BossEngine::Ref<BossEngine::VertexBuffer> m_VertexBuffer;
	BossEngine::Ref<BossEngine::IndexBuffer> m_IndexBuffer;

	/////////TEXTURE OBJECT//////////////////////////////////
	
	BossEngine::ShaderLibrary m_ShaderLibrary;
	BossEngine::Ref<BossEngine::Texture> m_Texture;

	/////////TEXTURE OBJECT//////////////////////////////////

	BossEngine::Ref<BossEngine::Texture> m_TextureOverlay;

	glm::vec3 m_ObjectPosition;
	glm::vec3 m_ObjectColor = { 0.2f, 0.3f,0.8f };
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