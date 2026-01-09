#pragma once

#include "Shader.h"
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>
#include "Texture.h"

namespace KE
{
	class AssetManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
	public:
		AssetManager() = default;
		~AssetManager() = default;

		Shader* loadShader(std::string_view name, const ShaderCodes& shaderCodes);
		Shader* getShader(std::string_view name) const;
		void unloadShader(std::string_view name);

		Texture* loadTexture(std::string_view name, std::string_view path);
		Texture* getTexture(std::string_view name) const;
		void unloadTexture(std::string_view name);

		static AssetManager& getInstance();
	};
}