#pragma once

#include <string>
#include <string_view>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

namespace KE
{
	class AssetManager;

	struct ShaderCodes
	{
		std::string vertexCode;
		std::string fragCode;
	};

	class Shader
	{
	private:
		uint32_t m_programID = 0;
		ShaderCodes m_shaderCodes;
		std::unordered_map<std::string, int> m_uniformCache;
	private:
		ShaderCodes loadShaders(std::string_view vertPath, std::string_view fragPath);
		void createShaderObjects(std::string_view vertPath, std::string_view fragPath);

		friend class AssetManager;
		Shader(std::string_view vertPath, std::string_view fragPath);
	public:
		Shader() = default;
		~Shader() noexcept;

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		Shader(Shader&& other) noexcept;
		Shader& operator=(Shader&& other) noexcept;

		void useProgram() const;

		int getUniformLocation(std::string_view name);

		void setUniformMat4(std::string_view name, const glm::mat4& value);
		void setUniformVec3(std::string_view name, const glm::vec3& value);
		void setUniformFloat(std::string_view name, float value);
		void setUniformInt(std::string_view name, int value);
	};
}
