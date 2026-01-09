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

		auto shader = std::make_unique<Shader>(shaderCodes.vertexCode, shaderCodes.fragCode);

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
	}
}