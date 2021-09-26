#include "pch.h"
#include "Renderer.h"

namespace LT {
	Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{

	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}
	void Renderer::BeginScene(glm::mat4 viewProjectionMatrix)
	{
		s_sceneData->ViewProjectionMatrix = viewProjectionMatrix;
	}
	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_viewProjection", s_sceneData->ViewProjectionMatrix);
		shader->SetMat4("u_modelMatrix", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}