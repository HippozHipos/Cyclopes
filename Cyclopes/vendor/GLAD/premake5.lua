project "GLAD"
	kind "StaticLib"
	staticruntime "On"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/GLAD/glad.h",
		"include/KHR/khrplatform.h",
        "src/glad.c"
	}

    includedirs
    {
        "include"
    }

    filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CYC_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "CYC_RELEASE"
		symbols "on"

