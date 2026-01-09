#pragma once

#include "Shader.h"
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>

namespace KE
{
	class AssetManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
	public:
		AssetManager() = default;
		~AssetManager() = default;

		Shader* loadShader(std::string_view name, const ShaderCodes& shaderCodes);
		Shader* getShader(std::string_view name) const;
		void unloadShader(std::string_view name);

		static AssetManager& getInstance();
	};
}