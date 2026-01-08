#include "Transform.h"

namespace KE
{
	const glm::mat4& Transform::getTransformMatrix() 
	{
		m_model = glm::mat4(1.f);

		m_model = glm::translate(m_model, m_position);

		m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
		m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f));
		m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.f, 0.f, 1.f));

		m_model = glm::scale(m_model, m_scale);

		return m_model;
	}
}
