#pragma once

#include "Core.h"

namespace LT {
	class LAPI Input
	{
	public:
		static bool isKeyPressed(int keyCode) { return s_Instance->isKeyPressedImpl(keyCode); }
		static bool istMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
		static float getMouseX() { return s_Instance->getMouseXImpl(); }
		static float getMouseY() { return s_Instance->getMouseYImpl(); }
		static std::pair<float, float> getMousePos(){ return s_Instance->getMousePosImpl(); }
	protected:
		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}
