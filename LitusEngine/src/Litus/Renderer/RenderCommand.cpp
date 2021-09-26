#include "pch.h"
#include "RenderCommand.h"

namespace LT {
	Scope<RenderAPI> RenderCommand::s_renderAPI = RenderAPI::Create();
}