workspace "Cyclopes"
	startproject "Sandbox"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Cyclopes/vendor/GLFW/include"
IncludeDir["GLAD"] = "Cyclopes/vendor/GLAD/include"
IncludeDir["spdlog"] = "Cyclopes/vendor/spdlog/include"
IncludeDir["ImGui"] = "Cyclopes/vendor/ImGui"
IncludeDir["glm"] = "Cyclopes/vendor/glm"

include "Cyclopes/vendor/GLFW"
include "Cyclopes/vendor/GLAD"
include "Cyclopes/vendor/ImGui"

project "Cyclopes"
	location "Cyclopes"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Cycpch.h"
	pchsource "Cyclopes/src/Cycpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}", 
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{prj.name}/src"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CYC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CYC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CYC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CYC_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}", 
		"Cyclopes/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"Cyclopes/src",
	}

	links
	{
		"Cyclopes",
	}

	filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"

		defines
		{
			"CYC_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		runtime "Debug"
		defines "CYC_DEBUG"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "CYC_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		defines "CYC_DIST"
		optimize "on"