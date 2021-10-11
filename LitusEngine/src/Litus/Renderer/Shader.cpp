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


	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		m_shaders[name] = shader;
	}
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		LT_CORE_ASSERT(Exists(name), "Shader does not exist in ShaderLibrary!");
		return m_shaders[name];

	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}
}