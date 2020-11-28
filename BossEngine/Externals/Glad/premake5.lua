project "Glad"
  kind "StaticLib"
  language "C"
  staticruntime "on"
  
  targetdir ("bin/" .. outputDir .. "/%{prj.name}")
  objdir ("obj/" ..outputDir .. "/%{prj.name}")
  
  files
  {
    "include/glad/glad.h",
    "include/KHR/khrplatform.h",
    "src/glad.c"
  }
  
  includedirs
  {
	"include"
  }
  
  filter "system:windows"
    systemversion "latest"

  -- filter configuration of VS
filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

filter "configurations:Release"
	runtime "Release"
	optimize "on"