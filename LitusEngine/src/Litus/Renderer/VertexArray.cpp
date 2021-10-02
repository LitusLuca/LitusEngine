#include "pch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"

namespace LT {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}
