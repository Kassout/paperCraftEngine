#pragma once

#ifdef PPCF_PLATFORM_WINDOWS
	#ifdef PPCF_BUILD_DLL
		#define PAPERCRAFT_API __declspec(dllexport)
	#else
		#define PAPERCRAFT_API __declspec(dllimport)
	#endif
#else
	#error PaperCraft only support Windows!
#endif