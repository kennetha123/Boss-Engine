#include "bepch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
namespace BossEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::API::Direct3D11:
			BE_CORE_ASSERT(false, "RendererAPI::Direct3D11 is currently not supported.");
			return nullptr;

		}

		BE_CORE_ASSERT(false, "Unknown Render API.");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		case RendererAPI::API::Direct3D11:
			BE_CORE_ASSERT(false, "RendererAPI::Direct3D11 is currently not supported.");
			return nullptr;

		}

		BE_CORE_ASSERT(false, "Unknown Render API.");
		return nullptr;

	}

}