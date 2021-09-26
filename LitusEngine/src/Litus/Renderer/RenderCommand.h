#pragma once
#include "RenderAPI.h"

namespace LT {
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_renderAPI->Init();
		}

		static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_renderAPI->SetViewPort(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_renderAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_renderAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			s_renderAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static Scope<RenderAPI> s_renderAPI;
	};
}
