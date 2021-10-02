#pragma once
#include "Litus\Renderer\Shader.h"

typedef unsigned int GLenum;

namespace LT {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);
		~OpenGLShader();

		void Bind() override;
		void Unbind() override;

		void SetInt(const std::string& name, int value) override;
		void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;

		const std::string& GetName() const override { return m_name; }

	private:
		std::unordered_map<GLenum, std::string>	PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSource);
		std::string ReadFile(const std::string& path);

	private:
		uint32_t m_RendererID;
		std::string m_name;
	};
}