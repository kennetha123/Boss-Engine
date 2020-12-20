#include "bepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace BossEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		case RendererAPI::API::Direct3D11:
			BE_CORE_ASSERT(false, "RendererAPI::Direct3D11 is currently not supported.");
			return nullptr;

		}

		BE_CORE_ASSERT(false, "Unknown Render API.");
		return nullptr;
	}

}