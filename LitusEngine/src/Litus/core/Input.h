#pragma once

#include "Core.h"

namespace LT {
	class LAPI Input
	{
	public:
		static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		static bool IstMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		static std::pair<float, float> GetMousePos(){ return s_Instance->GetMousePosImpl(); }
	protected:
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}
