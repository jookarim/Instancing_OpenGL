#pragma once

#include <GL/glew.h>
#include <cstdint>
#include <vector>

namespace KE
{
	template<typename T>

	class ShaderStorageBuffer
	{
	private:
		uint32_t m_ID;

		std::vector<T> m_data;

		void createSSBO(uint32_t bindingPoint, const std::vector<T>& data)
		{
			glCreateBuffers(1, &m_ID);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, m_ID);
			glNamedBufferStorage(m_ID, static_cast<GLsizeiptr>(data.size() * sizeof(T)), data.data(), GL_DYNAMIC_STORAGE_BIT);
			m_data = std::move(data);
		}

		void destroySSBO()
		{
			glDeleteBuffers(1, &m_ID);
			m_ID = 0;
		}
	public:
		ShaderStorageBuffer(uint32_t bindingPoint, const std::vector<T>& data)
		{
			createSSBO(bindingPoint, data);
		}

		~ShaderStorageBuffer()
		{
			destroySSBO();
		}

		void uploadData(const std::vector<T>& data)
		{
			m_data = data;

			glNamedBufferSubData(m_ID, 0, static_cast<GLsizeiptr>(data.size() * sizeof(T)), data.data());
		}

		uint32_t getID() const { return m_ID; }

		const std::vector<T>& getData() const { return m_data; }
	};
}
