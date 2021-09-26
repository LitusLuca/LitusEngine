#include "pch.h"
#include "RenderAPI.h"
#include "Platform\OpenGL\OpenGLRenderAPI.h"

namespace LT {
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	Scope<RenderAPI> RenderAPI::Create()
	{
		switch (s_API)
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None RenderAPI is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return std::make_unique<OpenGLRenderAPI>();
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}