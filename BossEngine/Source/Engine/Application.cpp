#include "bepch.h"
#include "Application.h"

#include "Engine/Log.h"

#include "Engine/Renderer/Renderer.h"

#include "Input.h"

namespace BossEngine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application()
	{
		// Check application is already created Instance.
		BE_CORE_ASSERT(!Instance, "Application Already Exist!");
		Instance = this;

		// Create window and setting Event Callback.
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// Setup ImGui on Application.
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

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
		   -0.5f, -0.5f, 0.0f,	 1.0f,	0.0f, 0.0f, 1.0f,	// bottom left
			0.5f, -0.5f, 0.0f,	 0.0f,  0.0f, 1.0f, 1.0f,	// bottom right
		   -0.5f,  0.5f, 0.0f,	 0.0f,  0.0f, 1.0f, 1.0f,	// top left
			0.5f,  0.5f, 0.0f,	 0.0f,  1.0f, 0.0f, 1.0f,	// top right
		};

		// Create Indices data. This should be in DCC later on.
		unsigned int indices[6] = { 0, 1, 2, 1, 2, 3 };

//////////////////////////////////////////////////////////////////////////////////////////
		// Vertex Shader and Fragment Shader.

		std::string vertexSource = R"(
			#version 330
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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
		m_VertexArray.reset(VertexArray::Create());

		// Create Vertex Buffer (need vertices data)
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// Create Buffer Layout so we can transform vertices data
		// into shader data.
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		// Set the layout into our Vertex Buffer.
		m_VertexBuffer->SetLayout(layout);

		// Add Vertex Buffer that has Layout into Vertex Array.
		// Make sure the Vertex Buffer already had a layout.
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Set ( Index Buffer / Element Buffer ) with indices.
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		// Vertex Array set the IBO / EBO.
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	
		// Set Vertex and Fragment Shader.
		m_Shader.reset(new Shader(vertexSource, fragmentSource));

//////////////////////////////////////////////////////////////////////////////////////////
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// Print all event.
		//BE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Rendering
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			{
				Renderer::BeginScene();

				m_Shader->Bind();
				Renderer::Submit(m_VertexArray);

				Renderer::EndScene();
			}

			// Layering
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}