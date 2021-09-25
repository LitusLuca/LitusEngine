#pragma once
#include "Litus\Event\Event.h"
#include "Time.h"

namespace LT {
	class LAPI Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Time dT) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& ev)  {}

		const std::string& GetName() const { return m_debugName; }

	private:
		std::string m_debugName;
	};
}
