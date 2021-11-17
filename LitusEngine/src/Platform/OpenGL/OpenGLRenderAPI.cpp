#include "pch.h"
#include "OpenGLRenderAPI.h"

#include "glad\glad.h"
namespace LT {
	void OpenGLMessageCallback(
		uint32_t source,
		uint32_t type,
		uint32_t id,
		uint32_t severity,
		int lenght,
		const char* message,
		const void* userParam
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:			LT_CORE_CRITICAL(message); break;
		case GL_DEBUG_SEVERITY_MEDIUM:			LT_CORE_ERROR(message); break;
		case GL_DEBUG_SEVERITY_LOW:				LT_CORE_INFO(message); break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	LT_CORE_TRACE(message); break;
		}

		LT_CORE_ASSERT(false, "Unknown Severity!");
	}
	void OpenGLRenderAPI::Init()
	{
		#ifdef LT_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif // LT_DEBUG
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRenderAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
		uint32_t indexCount = count ? count : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}