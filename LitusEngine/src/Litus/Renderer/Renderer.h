#pragma once
#include "RenderCommand.h"

#include "Shader.h"


namespace LT {
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(glm::mat4 viewProjectionMatrix);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);

		static RenderAPI::API GetApi() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* s_sceneData;
	};
}