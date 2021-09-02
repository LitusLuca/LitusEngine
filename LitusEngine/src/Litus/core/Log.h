#pragma once
#include "Core.h"
#include <spdlog\spdlog.h>
#include <spdlog\sinks\stdout_color_sinks.h>

namespace LT {
	class LAPI Log
	{
	public:
		static void init();

		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define LT_CORE_TRACE(...) ::LT::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LT_CORE_INFO(...) ::LT::Log::getCoreLogger()->info(__VA_ARGS__)
#define LT_CORE_WARN(...) ::LT::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LT_CORE_ERROR(...) ::LT::Log::getCoreLogger()->error(__VA_ARGS__)
#define LT_CORE_FATAL(...) ::LT::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define LT_TRACE(...) ::LT::Log::getClientLogger()->trace(__VA_ARGS__)
#define LT_INFO(...) ::LT::Log::getClientLogger()->info(__VA_ARGS__)
#define LT_WARN(...) ::LT::Log::getClientLogger()->warn(__VA_ARGS__)
#define LT_ERROR(...) ::LT::Log::getClientLogger()->error(__VA_ARGS__)
#define LT_FATAL(...) ::LT::Log::getClientLogger()->fatal(__VA_ARGS__)
