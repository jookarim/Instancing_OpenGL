#include "AssetManager.h"
#include <iostream>

namespace KE
{
	AssetManager& AssetManager::getInstance()
	{
		static AssetManager assetManager;
		return assetManager;
	}

	Shader* AssetManager::loadShader(std::string_view name, const ShaderCodes& shaderCodes)
	{
		auto key = std::string(name);

		auto it = m_shaders.find(key);

		if (it != m_shaders.end())
		{
			return it->second.get();
		}

		auto shader = std::unique_ptr<Shader>(new Shader(shaderCodes.vertexCode, shaderCodes.fragCode));

		m_shaders.emplace(key, std::move(shader));

		return m_shaders[key].get();
	}

	Shader* AssetManager::getShader(std::string_view name) const
	{
		auto key = std::string(name);

		auto it = m_shaders.find(key);

		if (it != m_shaders.end())
		{
			return it->second.get();
		}

		std::cerr << "Failed to get shader: " << name << "\n";

		return nullptr;
	}

	void AssetManager::unloadShader(std::string_view name)
	{
		auto key = std::string(name);

		auto it = m_shaders.find(key);

		if (it != m_shaders.end())
		{
			m_shaders.erase(key);
		}

		else
		{
			std::cerr << "Shader not found: " << name << "\n";
		}
	}

	Texture* AssetManager::loadTexture(std::string_view name, std::string_view path)
	{
		auto key = std::string(name);

		auto it = m_textures.find(key);

		if (it != m_textures.end())
		{
			return it->second.get();
		}

		auto texture = std::unique_ptr<Texture>(new Texture(path));

		m_textures.emplace(key, std::move(texture));

		return m_textures[key].get();
	}

	Texture* AssetManager::getTexture(std::string_view name) const
	{
		auto key = std::string(name);

		auto it = m_textures.find(key);

		if (it != m_textures.end())
		{
			return it->second.get();
		}

		std::cerr << "Failed to get texture: " << name << "\n";

		return nullptr;
	}

	void AssetManager::unloadTexture(std::string_view name)
	{
		auto key = std::string(name);

		auto it = m_textures.find(key);

		if (it != m_textures.end())
		{
			m_textures.erase(key);
		}
		
		else
		{
			std::cerr << "Failed to load texture: " << name << "\n";
		}
	}
}