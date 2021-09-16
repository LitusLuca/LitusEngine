#pragma once

#include "Litus\Renderer\Buffer.h"

namespace LT {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		void bind() const override;
		void unbind() const override;
	private:
		uint32_t m_rendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void bind() const override;
		void unbind() const override;
		uint32_t getCount() const override { return m_count; }
	private:
		uint32_t m_rendererID;
		uint32_t m_count;
	};
}