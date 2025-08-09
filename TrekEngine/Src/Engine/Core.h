#pragma once

#ifdef Trek_PLATFORM_WINDOWS
	#ifdef Trek_BUILD_DLL
		#define Trek_API __declspec(dllexport)
	#else
		#define Trek_API __declspec(dllimport)
	#endif
#endif