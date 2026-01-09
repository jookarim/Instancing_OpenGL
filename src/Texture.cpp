#include "Texture.h"
#include <iostream>

namespace KE
{
	void Texture::loadTexture(std::string_view path)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);

		stbi_uc* data = stbi_load(path.data(), &m_width, &m_height, &m_channels, 0);

		if (!data)
		{
			std::cerr << "Failed to load texture: " << path << "\n";
		}

		m_path = path;

		GLenum internalFormat;//how openGL stores pixel
		GLenum dataFormat; //how pixel stored in memory

		if (m_channels == 1)
		{
			internalFormat = GL_R8;
			dataFormat = GL_RED;
		}

		if (m_channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		if (m_channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}

		glTextureStorage2D(m_textureID, 1, internalFormat, m_width, m_height);
		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}

	void Texture::destroyTexture()
	{
		glDeleteTextures(1, &m_textureID);
		m_textureID = m_width = m_height = m_channels = 0;
	}

	Texture::Texture(std::string_view path)
	{
		loadTexture(path);
	}

	Texture::~Texture() noexcept
	{
		destroyTexture();
	}

	void Texture::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_textureID);
	}

	Texture::Texture(Texture&& other) noexcept
	{
		m_textureID = other.m_textureID;
		m_channels = other.m_channels;
		m_path = std::move(other.m_path);
		m_width = other.m_width;
		m_height = other.m_height;

		other.m_textureID = 0;
		other.m_channels = 0;
		other.m_width = 0;
		other.m_height = 0;
		other.m_path = "";
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		if (this != &other)
		{
			destroyTexture();

			m_textureID = other.m_textureID;
			m_channels = other.m_channels;
			m_path = std::move(other.m_path);
			m_width = other.m_width;
			m_height = other.m_height;

			other.m_textureID = 0;
			other.m_channels = 0;
			other.m_width = 0;
			other.m_height = 0;
			other.m_path = "";

			return *this;
		}

		return *this;
	}
}