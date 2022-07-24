workspace "PaperCraft"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PaperCraft"
	location "PaperCraft"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"

		defines
		{
			"PPCF_PLATFORM_WINDOWS",
			"PPCF_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PPCF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PPCF_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "PPCF_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PaperCraft/vendor/spdlog/include",
		"PaperCraft/src"
	}

	links
	{
		"PaperCraft"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"

		defines
		{
			"PPCF_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PPCF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PPCF_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "PPCF_DIST"
		symbols "On"
