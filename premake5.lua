workspace "LitusEngine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

IncludeDir = {}
IncludeDir["GLFW"] = "LitusEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "LitusEngine/vendor/GLAD/include"

include "LitusEngine/vendor/GLFW"
include "LitusEngine/vendor/GLAD"

project "LitusEngine"
	location "LitusEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}

	links {
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines {
			"LT_PLATFORM_WINDOWS",
			"LT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "LT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LT_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"LitusEngine/vendor/spdlog/include",
		"LitusEngine/src"
	}

	links {
		"LitusEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines {
			"LT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LT_DIST"
		optimize "On"