#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform\OpenGL\OpenGlBuffer.h"

namespace LT {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::getApi())
		{
		case RendererAPI::None: LT_CORE_ASSERT(false, "None Renderer is not supported!");
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::getApi())
		{
		case RendererAPI::None: LT_CORE_ASSERT(false, "None Renderer is not supported!");
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
	}
}