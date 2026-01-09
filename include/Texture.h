#pragma once

#include <GL/glew.h>
#include "stb/stb_image.h"
#include <string>
#include <string_view>

namespace KE
{
	class Texture
	{
	private:
		uint32_t m_textureID{};
		int m_width, m_height, m_channels;
		std::string m_path;

		void loadTexture(std::string_view path);
		void destroyTexture();
	public:
		Texture(std::string_view path);
		~Texture() noexcept;

		void bind(uint32_t slot = 0) const;

		uint32_t getID() const { return m_textureID; }
		int getWidth() const { return m_height; }
		int getHeight() const { return m_height; }
		int getChannels() const { return m_channels; }
		const std::string& getPath() const { return m_path; }

		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;

		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;
	};
}
