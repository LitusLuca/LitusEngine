#include "Litus\core\Input.h"

namespace LT {
	class WindowsInput : public Input
	{
	protected:
		bool isKeyPressedImpl(int keycode) override;

		bool isMouseButtonPressedImpl(int button) override;
		std::pair<float, float> getMousePosImpl() override;
		float getMouseXImpl() override;
		float getMouseYImpl() override;
	};
}