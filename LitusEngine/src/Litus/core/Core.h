#pragma once

#ifdef LT_PLATFORM_WINDOWS
	#ifdef LT_DYNAMIC_LINK
		#ifdef LT_BUILD_DLL
			#define LAPI __declspec(dllexport)
		#else
			#define LAPI __declspec(dllimport)
		#endif // LT_BUILD_DLL
	#else
		#define LAPI
	#endif
#else
	#error LitusEngine only supports windows
#endif // LT_PLATFORM_WINDOWS

#ifdef LT_DEBUG
#define LT_ENABLE_ASSERTS
#endif // LT_DEBUG


#ifdef LT_ENABLE_ASSERTS
#define LT_ASSERT(x, ...) { if(!(x)){LT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define LT_CORE_ASSERT(x, ...) { if(!(x)){LT_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define LT_ASSERT(X, ...)
#define LT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define LT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)