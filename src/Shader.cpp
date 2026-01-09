#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace KE
{
	ShaderCodes Shader::loadShaders(std::string_view vertPath,
		std::string_view fragPath)
	{
		ShaderCodes shaderCodes{};

		std::ifstream vertFile(vertPath.data());
		if (!vertFile.is_open())
		{
			std::cerr << "Failed to open vertex shader file: "
				<< vertPath << "\n";
			return {};
		}

		std::stringstream ss;
		ss << vertFile.rdbuf();
		shaderCodes.vertexCode = ss.str();

		ss.str("");
		ss.clear();

		std::ifstream fragFile(fragPath.data());
		if (!fragFile.is_open()) //corrected condition
		{
			std::cerr << "Failed to open fragment shader file: "
				<< fragPath << "\n";
			return {};
		}

		ss << fragFile.rdbuf();
		shaderCodes.fragCode = ss.str();

		std::cout << "Loaded shaders correctly: "
			<< vertPath << "  " << fragPath << "\n";

		return shaderCodes;
	}

	void Shader::createShaderObjects(std::string_view vertPath,
		std::string_view fragPath)
	{
		m_shaderCodes = loadShaders(vertPath, fragPath);
		
		uint32_t vertShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexCode = m_shaderCodes.vertexCode.c_str();
		glShaderSource(vertShader, 1, &vertexCode, nullptr);
		glCompileShader(vertShader);//combiled vertex shader

		uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragCode = m_shaderCodes.fragCode.c_str();
		glShaderSource(fragShader, 1, &fragCode, nullptr);
		glCompileShader(fragShader);//combiled frag shader

		m_programID = glCreateProgram();
		glAttachShader(m_programID, vertShader);
		glAttachShader(m_programID, fragShader);

		//corrected order of program link/detach/delete
		glLinkProgram(m_programID);
	
		glDetachShader(m_programID, vertShader);
		glDetachShader(m_programID, fragShader);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	Shader::Shader(std::string_view vertPath,
		std::string_view fragPath)
	{
		createShaderObjects(vertPath, fragPath);
	}

	Shader::~Shader()
	{
		if (m_programID != 0)
			glDeleteProgram(m_programID);
	}

	void Shader::useProgram() const
	{
		glUseProgram(m_programID);
	}

	Shader::Shader(Shader&& other) noexcept
	{
		m_programID = other.m_programID;
		m_shaderCodes = std::move(other.m_shaderCodes);

		other.m_programID = 0;
		other.m_shaderCodes = {};
	}

	Shader& Shader::operator=(Shader&& other) noexcept
	{
		if (this != &other)
		{
			if (m_programID != 0)
				glDeleteProgram(m_programID);

			m_programID = other.m_programID;
			m_shaderCodes = std::move(other.m_shaderCodes);

			other.m_programID = 0;
			other.m_shaderCodes = {};
		}
		return *this;
	}

	int Shader::getUniformLocation(std::string_view name)
	{
		auto key = std::string(name);

		auto it = m_uniformCache.find(key);

		if (it != m_uniformCache.end())
		{
			return it->second;
		}

		int loc = glGetUniformLocation(m_programID, name.data());

		if (loc == -1)
		{
			std::cerr << "Failed to get Uniform: " << name << "\n";
		}

		m_uniformCache.emplace(key, loc);

		return loc;
	}

	void Shader::setUniformMat4(std::string_view name,
		const glm::mat4& value)
	{
		int loc = getUniformLocation(name);
		if (loc != -1)
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setUniformVec3(std::string_view name,
		const glm::vec3& value)
	{
		int loc = getUniformLocation(name);
		if (loc != -1)
			glUniform3fv(loc, 1, glm::value_ptr(value));
	}

	void Shader::setUniformFloat(std::string_view name, float value)
	{
		int loc = getUniformLocation(name);
		if (loc != -1)
			glUniform1f(loc, value);
	}

	void Shader::setUniformInt(std::string_view name, int value)
	{
		int loc = getUniformLocation(name);
		if (loc != -1)
			glUniform1i(loc, value);
	}
}
