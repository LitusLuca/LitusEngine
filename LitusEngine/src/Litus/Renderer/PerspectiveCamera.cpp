#include "pch.h"
#include "PerspectiveCamera.h"
#include <glm\gtx\transform.hpp>

namespace LT {
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane)
		: m_view(glm::lookAt(m_position, m_position + m_front, m_worldUp))
	{
		m_projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		m_viewProjection = m_projection * m_view;
	}
	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		m_projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		m_viewProjection = m_projection * m_view;
	}
	void PerspectiveCamera::RecalculateViewMatrix()
	{
		m_view = glm::lookAt(m_position, m_position + m_front, m_worldUp);
		m_viewProjection = m_projection * m_view;
	}
	void PerspectiveCamera::RecalculateFrontVector()
	{
		m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front.y = sin(glm::radians(m_pitch));
		m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	}
}