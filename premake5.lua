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
IncludeDir["ImGui"] = "LitusEngine/vendor/ImGui"
IncludeDir["glm"] = "LitusEngine/vendor/glm"
IncludeDir["stb_image"] = "LitusEngine/vendor/stb_image"

include "LitusEngine/vendor/GLFW"
include "LitusEngine/vendor/GLAD"
include "LitusEngine/vendor/ImGui"

project "LitusEngine"
	location "LitusEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}
	
	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
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
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"LitusEngine/vendor",
		"LitusEngine/vendor/spdlog/include",
		"LitusEngine/src",
		"%{IncludeDir.glm}"
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

project "plyLoader"
	location "plyLoader"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"LitusEngine/src/Litus/Utils"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "on"

	filter "configurations:Release"
		optimize "On"

	filter "configurations:Dist"
		optimize "On"