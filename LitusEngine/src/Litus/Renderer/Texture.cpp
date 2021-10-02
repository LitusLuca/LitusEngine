#include "pch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLTexture.h"

namespace LT {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}
		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}