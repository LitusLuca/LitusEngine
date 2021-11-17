#pragma once
#include "PerspectiveCamera.h"
#include "Litus\core\Time.h"

#include "Litus\Event\ApplicationEvents.h"
#include "Litus\Event\MouseEvents.h"
#include "Litus\Event\KeyEvents.h"

namespace LT {
	class FPSCameraController
	{
	public:
		FPSCameraController(float fov, float aspectRation, float nearPlane, float farPlane,
			float speed = 5.f, float sensitivity = 1.f);

		void OnUpdate(Time dt);
		void OnEvent(Event& ev);

		void OnResize(float width, float height);

		PerspectiveCamera& GetCamera() { return m_camera; }
		const PerspectiveCamera& GetCamera() const { return m_camera; }

		void SetSpeed(float speed) { m_speed = speed; }
		void SetMouseSensivity(float sens) { m_sens = sens; }
		
		float GetSpeed() const { return m_speed; }
		float GetMouseSensivity() const { return m_sens; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& ev);
		bool OnWindowResize(WindowResizeEvent& ev);
		bool OnMouseMoved(MouseMovedEvent& ev);
	private:
		PerspectiveCamera m_camera;
		glm::vec3 m_movingDir;

		float m_speed = 10.f, m_sens = 1.f;

		float m_fov, m_aspect, m_near, m_far;

		glm::vec2 m_mousePos = { 0.f, 0.f };
	};
}
