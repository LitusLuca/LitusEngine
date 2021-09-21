#include "pch.h"

#include "Shader.h"
#include "Platform\OpenGL\OpenGLShader.h"
#include "Renderer.h"


namespace LT {
	Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetApi())
		{
		case RenderAPI::API::None: LT_CORE_ASSERT(false, "None Renderer is not supported!");
		case RenderAPI::API::OpenGL: return new OpenGLShader(name, vertexSrc, fragmentSrc);
		}

		LT_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}