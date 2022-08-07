#pragma once

// If platform Windows.
#ifdef PPCF_PLATFORM_WINDOWS
	// If build DLL.
	#ifdef PPCF_BUILD_DLL
		#define PAPERCRAFT_API __declspec(dllexport)
	#else
		#define PAPERCRAFT_API __declspec(dllimport)
	#endif
#else
	#error PaperCraft only support Windows!
#endif

// Bitwise operation.
#define BIT(x) (1 << x)