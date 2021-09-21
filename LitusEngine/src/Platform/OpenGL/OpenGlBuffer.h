#pragma once

#include "Litus\Renderer\Buffer.h"

namespace LT {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		const BufferLayout& GetLayout() const override { return m_layout; }
		void SetLayout(const BufferLayout& layout) override { m_layout = layout; }

	private:
		uint32_t m_rendererID;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
		uint32_t GetCount() const override { return m_count; }
	private:
		uint32_t m_rendererID;
		uint32_t m_count;
	};
}