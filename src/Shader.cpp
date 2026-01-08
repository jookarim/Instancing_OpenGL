#include "Shader.h"
#include <iostream>

namespace KE
{
	const ShaderCodes& Shader::loadShaders(std::string_view vertPath, std::string_view fragPath)
	{
		ShaderCodes shaderCodes{};

		std::ifstream vertFile(vertPath.data());

		if (!(vertFile.is_open() || vertFile.good()))
		{
			std::cerr << "Failed to open vertex shader file: " << vertPath << "\n";
			return ShaderCodes{};
		}

		std::stringstream ss;
		ss >> vertFile.rdbuf();
		
		shaderCodes.vertexCode = ss.str();
		
		ss.clear();

		std::ifstream fragFile(fragPath.data());

		if (!(fragFile.is_open() || fragFile.good()))
		{
			std::cerr << "Failed to open frag shader file: " << fragPath << "\n";
			return ShaderCodes{};
		}

		ss >> fragFile.rdbuf();

		shaderCodes.fragCode = ss.str();

		std::cout << "Loaded shaders correctly: " << vertPath << "	" << fragPath << "\n";

		return shaderCodes;
	}

	void Shader::createShaderObjects(std::string_view vertPath, std::string_view fragPath)
	{
		ShaderCodes shaderCodes = loadShaders(vertPath, fragPath);

		uint32_t vertShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexCode = shaderCodes.vertexCode.c_str();
		glShaderSource(vertShader, 1, &vertexCode, nullptr);

		uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragCode = shaderCodes.fragCode.c_str();
		glShaderSource(fragShader, 1, &fragCode, nullptr);

		m_programID = glCreateProgram();
		glAttachShader(m_programID, vertShader);
		glAttachShader(m_programID, fragShader);

		glDetachShader(m_programID, vertShader);
		glDetachShader(m_programID, fragShader);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		glLinkProgram(m_programID);
	}

	Shader::Shader(std::string_view vertPath, std::string_view fragPath)
	{
		createShaderObjects(vertPath, fragPath);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_programID);
	}

	void Shader::useProgram() const
	{
		glUseProgram(m_programID);
	}

	Shader::Shader(Shader&& other)
	{
		m_programID = other.m_programID;
		m_shaderCodes = std::move(other.m_shaderCodes);

		other.m_programID = 0;
		m_shaderCodes = {};
	}

	Shader& Shader::operator=(Shader&& other)
	{
		if (this == &other) return *this;
		
		this->~Shader();

		m_programID = other.m_programID;
		m_shaderCodes = std::move(other.m_shaderCodes);

		other.m_programID = 0;
		m_shaderCodes = {};

		return *this;
	}

	int Shader::getUniformLocation(std::string_view name)
	{
		int loc = glGetUniformLocation(m_programID, name.data());

		if (loc == -1)
		{
			std::cerr << "Failed to get Uniform: " << name << "\n";
			return -1;
		}

		return 0;
	}

	void Shader::setUniformMat4(std::string_view name, const glm::mat4& value)
	{
		int loc = getUniformLocation(name);

		if (loc != -1)
		{
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
		}
	}

	void Shader::setUniformVec3(std::string_view name, const glm::vec3& value)
	{
		int loc = getUniformLocation(name);

		if (loc != -1)
		{
			glUniform3fv(loc, 1, glm::value_ptr(value));
		}
	}

	void Shader::setUniformFloat(std::string_view name, float value)
	{
		int loc = getUniformLocation(name);

		if (loc != -1)
		{
			glUniform1f(loc, value);
		}
	}

	void Shader::setUniformInt(std::string_view name, int value)
	{
		int loc = getUniformLocation(name);

		if (loc != -1)
		{
			glUniform1i(loc, value);
		}
	}
}
