#include "pch.h"

#include "Shader.h"
#include "Platform\OpenGL\OpenGLShader.h"
#include "Renderer.h"


namespace LT {
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLShader>(path);
		}

		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}