#include "bepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace BossEngine
{
	Shader* Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(path);
		case RendererAPI::API::Direct3D11:
			BE_CORE_ASSERT(false, "RendererAPI::Direct3D11 is currently not supported.");
			return nullptr;

		}

		BE_CORE_ASSERT(false, "Unknown Render API.");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		case RendererAPI::API::Direct3D11:
			BE_CORE_ASSERT(false, "RendererAPI::Direct3D11 is currently not supported.");
			return nullptr;

		}

		BE_CORE_ASSERT(false, "Unknown Render API.");
		return nullptr;
	}

}