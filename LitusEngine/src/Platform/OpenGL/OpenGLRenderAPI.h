#pragma once
#include "Litus\Renderer\RenderAPI.h"

namespace LT {
	class OpenGLRenderAPI
		: public RenderAPI
	{
	public:
		void Init() override;
		void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4 & color) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>&vertexArray, uint32_t count = 0) override;
	};
}