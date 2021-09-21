#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform\OpenGL\OpenGlBuffer.h"

namespace LT {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!");
		case RenderAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!");
		case RenderAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}