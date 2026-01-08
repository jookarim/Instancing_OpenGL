#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace KE
{
	class Transform
	{
	private:
		glm::vec3 m_position{};
		glm::vec3 m_rotation{};
		glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
		glm::mat4 m_model = glm::mat4(1.f);
	public:
		Transform() = default;
		~Transform() = default;

		void setPosition(const glm::vec3& position) { m_position = position; }
		void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }
		void setScale(const glm::vec3& scale) { m_scale = scale; }

		const glm::vec3& getPosition() const { return m_position; }
		const glm::vec3& getRotation() const { return m_rotation; }
		const glm::vec3& getScale() const { return m_scale; }

		const glm::mat4& getTransformMatrix();
	};
}


