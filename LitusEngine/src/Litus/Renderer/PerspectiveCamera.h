#pragma once
#include "Camera.h"

namespace LT {
	class PerspectiveCamera
		: public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRation, float nearPlane, float farPlane, glm::vec3 worldUp = { 0.f, 1.f, 0.f });
		~PerspectiveCamera() = default;

		void SetProjection(float fov, float aspectRation, float nearPlane, float farPlane);

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }

		std::pair<float, float> GetRoation() const { return { m_yaw, m_pitch }; }
		float GetYaw() const { return m_yaw; }
		float GetPitch() const { return m_pitch; }
		void SetRotation(float yaw, float pitch) { m_yaw = yaw; m_pitch = pitch; RecalculateFrontVector(); RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_projection; }
		const glm::mat4& GetViewMatrix() const { return m_view; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjection; }
	private:
		void RecalculateViewMatrix();
		void RecalculateFrontVector();
	private:
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;

		glm::vec3 m_position = { 0.f, 0.f ,0.f };
		glm::vec3 m_front = { 0.f, 0.f, -1.f };
		glm::vec3 m_worldUp;
		float m_yaw = -90.f;
		float m_pitch = 0.f;
	};
}
