#pragma once
#include "Litus/Renderer/VertexArray.h"

namespace LT {
    class OpenGLVertexArray :
        public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        void Bind() override;
        void Unbind() override;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }

    private:
        uint32_t m_rendererID;
        uint32_t m_vertexBufferIndex = 0;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
}

