#include "pch.h"
#include "RenderCommand.h"

namespace LT {
	std::unique_ptr<RenderAPI> RenderCommand::s_renderAPI = RenderAPI::Create();
}