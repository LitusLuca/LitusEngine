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
	#error Litus only supports windows
#endif // LT_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
#define LT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)