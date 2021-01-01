#include "bepch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace BossEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		case RendererAPI::API::Direct3D11:
			BE_CORE_ASSERT(false, "RendererAPI::Direct3D11 is currently not supported.");
			return nullptr;

		}

		BE_CORE_ASSERT(false, "Unknown Render API.");
		return nullptr;
	}
}