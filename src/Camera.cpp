#include "Camera.h"

namespace KE
{
	glm::mat4 Camera::getViewMatrix() const
	{
		glm::mat4 view = glm::lookAt(m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
		return view;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		glm::mat4 proj = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
		return proj;
	}
}