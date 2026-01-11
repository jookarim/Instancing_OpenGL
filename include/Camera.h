#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace KE
{
	class Camera
	{
	private:
		glm::vec3 m_position{0.f, 0.f, 3.f};
			
		float m_fov{ 45.f };
		float m_near{ 0.1f };
		float m_far{ 1000.f };
		float m_aspect{ 4.f / 3.f };
	public:
		Camera() = default;
		~Camera() = default;

		void setPosition(const glm::vec3& position) { m_position = position; }
		void setFov(float fov) { m_fov = fov; }
		void setNear(float near) { m_near = near; }
		void setFar(float far) { m_far = far; }
		void setAspect(int width, int height) { m_aspect = static_cast<float>(width) / static_cast<float>(height); }

		const glm::vec3& getPosition() const { return m_position; }
		float getFov() const { return m_fov; }
		float getNear() const { return m_near; }
		float getFar() const { return m_far; }
		float getAspect() const { return m_aspect; }

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;
	};
}