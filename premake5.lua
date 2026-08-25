workspace "Surpass-Core"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	

project "Surpass-Core"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"
	debugdir "%{prj.location}"

	pchheader "sppch.h"
	pchsource "src/sppch.cpp"

	files {
		"src/**.h",
		"src/**.cpp",
		"lib/glad/src/glad.c",
		"src/sppch.cpp"
	}

	includedirs {
		"src",
		"lib/glfw/include",
		"lib/glad/include",
		"lib/stb/"
	}

	libdirs {
		"lib/glfw/lib"
	}

	links {
		"glfw3",
		"opengl32"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "On"