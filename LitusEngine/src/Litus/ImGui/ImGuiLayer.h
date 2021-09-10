#pragma once
#include "Litus\core\Layer.h"

namespace LT {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onImGuiRender() override;

		void begin();
		void end();
		
	private:
		float m_time = 0.f;

	};
}