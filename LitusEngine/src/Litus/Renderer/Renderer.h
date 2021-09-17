#pragma once


namespace LT {
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		static RendererAPI GetApi() { return s_rendererAPI; }

	private:
		static RendererAPI s_rendererAPI;
	};
}