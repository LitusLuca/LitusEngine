#pragma once
#include "Litus\core\Layer.h"

namespace LT {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
		
	private:
		float m_time = 0.f;

	};
}