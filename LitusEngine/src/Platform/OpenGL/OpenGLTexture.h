#pragma once
#include "Litus\Renderer\Texture.h"

#include <glad\glad.h>

namespace LT {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		uint32_t GetWidth() const override { return m_width; }
		uint32_t GetHeight() const override { return m_height; }
		uint32_t GetRenderID() const override { return m_renderID; }

		void SetData(void* data, uint32_t size) override;
		void Bind(uint32_t slot = 0) const override;
		bool IsLoaded() const override { return m_isLoaded; }
		bool operator==(const Texture& other) const override
		{
			return m_renderID == ((OpenGLTexture2D&)other).m_renderID;
		}

	private:
		uint32_t m_renderID;
		std::string m_path;
		uint32_t m_width, m_height;
		GLenum m_internalFormat, m_dataFormat;

		bool m_isLoaded;
	};
}
