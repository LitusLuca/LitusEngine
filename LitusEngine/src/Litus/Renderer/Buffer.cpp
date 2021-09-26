#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform\OpenGL\OpenGlBuffer.h"

namespace LT {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!");
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!");
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}