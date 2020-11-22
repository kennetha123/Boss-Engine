workspace "BossEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

-- output directory name
	
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directory relative to folder
IncludeDir = {}
IncludeDir["GLFW"] = "BossEngine/Externals/GLFW/include"
IncludeDir["Glad"] = "BossEngine/Externals/Glad/include"

include "BossEngine/Externals/GLFW"
include "BossEngine/Externals/Glad"

-------------------------------------------------------------------------------------
------------------------ Engine project ---------------------------------------------	
-------------------------------------------------------------------------------------

-- This is Engine VS Project creation.
project "BossEngine"
	location "BossEngine"	-- folder location name
	kind "SharedLib"		-- set to sharedLib for dll.
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")	-- this for the output of .exe file.
	objdir ("obj/" .. outputDir .. "/%{prj.name}")		-- the output of .obj file generated by scripts.
	
	-- precompile header
	pchheader "bepch.h"
	pchsource "BossEngine/Source/bepch.cpp"
	
	-- take the whole file inside project
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"		
	}
	
	-- include external libs.
	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Externals/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		-- Linking input definition.
		defines
		{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL"
		}
		
		-- we're copying the .dll file from Engine to the game .exe
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Game")
		}
		
-- filter configuration of VS
	filter "configurations:Debug"
		defines "BE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "BE_RELEASE"
		buildoptions "/MD"
		optimize "On"
	
	filter "configurations:Distribution"
		defines "BE_DIST"
		buildoptions "/MD"
		optimize "On"	
		
		
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
	
	-- including all External libs + Engine
	includedirs
	{
		"BossEngine/Externals/spdlog/include",
		"BossEngine/Source"
	}
	
	-- Add linking to the engine so the game can use Engine API.
	links
	{
		"BossEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BE_PLATFORM_WINDOWS"
		}
		
-- filter configuration of VS		
	filter "configurations:Debug"
		defines "BE_DEBUG"
		buildoptions "/MDd"	
		symbols "On"
	
	filter "configurations:Release"
		defines "BE_RELEASE"
		buildoptions "/MD"	
		optimize "On"
	
	filter "configurations:Distribution"
		defines "BE_DIST"
		buildoptions "/MD"
		optimize "On"	