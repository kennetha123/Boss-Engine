#pragma once

namespace BossEngine
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
		Direct3D11 = 2
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:

		static RendererAPI s_RendererAPI;
	};
}