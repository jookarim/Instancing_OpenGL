#pragma once

#include <GL/glew.h>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace KE
{
	struct ShaderCodes
	{
		std::string vertexCode = "";
		std::string fragCode = "";
	};

	class Shader
	{
	private:
		uint32_t m_programID{};
		ShaderCodes m_shaderCodes{};

		const ShaderCodes& loadShaders(std::string_view vertexPath, std::string_view fragPath);
		void createShaderObjects(std::string_view vertPath, std::string_view fragPath);

		int getUniformLocation(std::string_view name);
	public:
		Shader(std::string_view vertexPath, std::string_view fragPath);
		~Shader() noexcept;

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		Shader(Shader&& other);
		Shader& operator=(Shader&& other);

		uint32_t getID() const { return m_programID; }

		void useProgram() const;

		void setUniformMat4(std::string_view name, const glm::mat4& value);
		void setUniformVec3(std::string_view name, const glm::vec3& value);
		void setUniformInt(std::string_view name, int value);
		void setUniformFloat(std::string_view name, float value);

		const ShaderCodes& getShaderCodes() const { return m_shaderCodes; }
	};
}
