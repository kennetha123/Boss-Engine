workspace "BossEngine"
	architecture "x64"
		
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}
	
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-------------------------------------------------------------------------------------
------------------------ Engine project ---------------------------------------------	
-------------------------------------------------------------------------------------

project "BossEngine"
	location "BossEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("obj/" .. outputDir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"		
	}
	
	includedirs
	{
		"%{prj.name}/Externals/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.18362.0"
		
		defines
		{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Game")
		}
		
	filter "configurations:Debug"
		defines "BE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "BE_RELEASE"
		symbols "On"
	
	filter "configurations:Distribution"
		defines "BE_DIST"
		symbols "On"	
		
		
-------------------------------------------------------------------------------------
------------------------ Game project -----------------------------------------------		
-------------------------------------------------------------------------------------
		
project "Game"
	location "Game"
	kind "ConsoleApp"	
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("obj/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"		
	}
	
	includedirs
	{
		"BossEngine/Externals/spdlog/include",
		"BossEngine/Source"
	}
	
	links
	{
		"BossEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.18362.0"
		
		defines
		{
			"BE_PLATFORM_WINDOWS"
		}
				
	filter "configurations:Debug"
		defines "BE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "BE_RELEASE"
		symbols "On"
	
	filter "configurations:Distribution"
		defines "BE_DIST"
		symbols "On"	