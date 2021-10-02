#include "pch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"

namespace LT {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = nullptr;

		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		LT_CORE_ASSERT(data, "../Texture file could not be found!");
		if (data)
		{
			m_isLoaded = true;

			m_width = width;
			m_height = height;

			GLenum internalformat = 0, dataformat = 0;
			if (channels == 4)
			{
				internalformat = GL_RGBA8;
				dataformat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalformat = GL_RGB8;
				dataformat = GL_RGB;
			}
			m_internalFormat = internalformat;
			m_dataFormat = dataformat;

			LT_CORE_ASSERT(m_dataFormat & m_internalFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_renderID);
			glTextureStorage2D(m_renderID, 1, m_internalFormat, m_width, m_height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			glTextureSubImage2D(m_renderID, 0, 0, 0, m_width, m_height, dataformat, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
	{
		m_internalFormat = GL_RGBA8;
		m_dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_renderID);
		glTextureStorage2D(m_renderID, 1, m_internalFormat, width, height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_renderID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
		LT_CORE_ASSERT(size == bpp * m_width * m_height, "Data is not in the given size!");

		glTextureSubImage2D(m_renderID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_renderID);
	}
}

