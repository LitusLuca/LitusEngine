#pragma once

#ifdef LT_PLATFORM_WINDOWS
	#ifdef LT_BUILD_DLL
		#define LAPI __declspec(dllexport)
	#else
		#define LAPI __declspec(dllimport)
	#endif // LT_BUILD_DLL
#else
	#error Litus only supports windows
#endif // LT_PLATFORM_WINDOWS
