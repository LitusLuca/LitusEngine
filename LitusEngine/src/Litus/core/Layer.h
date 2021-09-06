#pragma once
#include "Litus\Event\Event.h"

namespace LT {
	class LAPI Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& ev)  {}

		const std::string& getName() const { return m_debugName; }

	private:
		std::string m_debugName;
	};
}
