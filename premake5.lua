workspace "Surpass-Core"
	startproject "Surpass-Core"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}"

IncludeDir = {}
IncludeDir["GLFW"] = "lib/glfw/include"
IncludeDir["GLAD"] = "lib/glad/include"
IncludeDir["STB"] = "lib/stb"
IncludeDir["GLM"] = "lib/glm"

group "Library"
	include "lib/glfw"
	include "lib/glad"
group ""

project "Surpass-Core"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "%{prj.location}"

	pchheader "sppch.h"
	pchsource "src/sppch.cpp"

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.GLM}"
	}

	links {
		"GLFW",
		"GLAD",
		"opengl32"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "on"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "on"