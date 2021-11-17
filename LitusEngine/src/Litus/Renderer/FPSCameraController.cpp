#include "pch.h"
#include "FPSCameraController.h"

#include "Litus\core\Input.h"
#include "Litus\core\KeyCodes.h"

namespace LT {
	FPSCameraController::FPSCameraController(float fov, float aspectRatio, float nearPlane, float farPlane,
		float speed, float sensitivity) 
		: m_fov(fov), m_aspect(aspectRatio), m_near(nearPlane), m_far(farPlane), m_speed(speed), m_sens(sensitivity), m_movingDir(0.f),
		m_camera(fov, aspectRatio, nearPlane, farPlane)
	{
		m_movingDir.x = cos(m_camera.GetYaw());
		m_movingDir.z = sin(m_camera.GetYaw());
	}
	void FPSCameraController::OnUpdate(Time dt)
	{
		glm::vec3 pos = m_camera.GetPosition();
		if (LT::Input::IsKeyPressed(LT_KEY_W))
			pos += m_movingDir * dt.GetSeconds() * m_speed;
		if (LT::Input::IsKeyPressed(LT_KEY_S))
			pos -= m_movingDir * dt.GetSeconds() * m_speed;
		if (LT::Input::IsKeyPressed(LT_KEY_A))
			pos -= glm::normalize(glm::cross(m_movingDir, glm::vec3(0.f, 1.f, 0.f))) * dt.GetSeconds() * m_speed;
		if (LT::Input::IsKeyPressed(LT_KEY_D))
			pos += glm::normalize(glm::cross(m_movingDir, glm::vec3(0.f, 1.f, 0.f))) * dt.GetSeconds() * m_speed;
		m_camera.SetPosition(pos);
	}
	void FPSCameraController::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<MouseMovedEvent>(LT_BIND_EVENT_FN(FPSCameraController::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(LT_BIND_EVENT_FN(FPSCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LT_BIND_EVENT_FN(FPSCameraController::OnWindowResize));
	}
	void FPSCameraController::OnResize(float width, float height)
	{
		m_aspect = width / height;
		m_camera.SetProjection(m_fov, m_aspect, m_near, m_far);
	}
	bool FPSCameraController::OnMouseScrolled(MouseScrolledEvent& ev)
	{
		m_fov -= ev.getYOffset() * 10.f;
		if (m_fov > 90.f) m_fov = 90.f;
		else if (m_fov < 25.f) m_fov = 25.f;
		m_camera.SetProjection(m_fov, m_aspect, m_near, m_far);
		return false;
	}
	bool FPSCameraController::OnWindowResize(WindowResizeEvent& ev)
	{
		OnResize((float)ev.GetWidth(), (float)ev.GetHeight());
		return false;
	}
	bool FPSCameraController::OnMouseMoved(MouseMovedEvent& ev)
	{
		auto [yaw, pitch] = m_camera.GetRoation();
		float xOffset = ev.GetX() - m_mousePos.x;
		float yOffset = m_mousePos.y - ev.GetY();
		yaw += m_sens * xOffset;
		pitch += m_sens * yOffset;
		if (pitch > 89.9f) pitch = 89.9f;
		else if (pitch < -89.9f) pitch = -89.9f;
		m_camera.SetRotation(yaw, pitch);
		m_movingDir.x = cos(glm::radians(yaw));
		m_movingDir.z = sin(glm::radians(yaw));
		m_mousePos.x = ev.GetX();
		m_mousePos.y = ev.GetY();
		return false;
	}
}