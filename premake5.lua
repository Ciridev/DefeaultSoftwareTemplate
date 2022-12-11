workspace "Default"
  architecture "x64"
  configurations { "Debug", "Release", "Distribution" }
  startproject "Default"

  outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
  ExtLibs = {}
  ExtLibs["Glad"]  = "build/ThirdParty/Glad/include"
  ExtLibs["GLFW"]  = "build/ThirdParty/GLFW/include"
  ExtLibs["ImGui"] = "build/ThirdParty/ImGui"

  IncludeDirectories = {}
  IncludeDirectories["glm"] = "build/ThirdParty/glm"

  include "build/ThirdParty/Glad"
  include "build/ThirdParty/GLFW"
  include "build/ThirdParty/ImGui"
  
  project "Default"
    location "build"
    language "C++"
    cppdialect "C++17"

    targetdir ( "bin/".. outputdir .. "/%{prj.name}" )
    objdir    ( "bin/intermediates/" .. outputdir .. "/%{prj.name}" )

    files
    { 
      "build/src/**.cpp", 
      "build/include/**.h",
      "%{IncludeDirectories.glm}/glm/**.hpp",
    }

    includedirs 
    {
      "build/src", 
      "build/include",
      "%{IncludeDirectories.glm}",
      "%{ExtLibs.Glad}", 
      "%{ExtLibs.GLFW}", 
      "%{ExtLibs.ImGui}",
    }

    links { "Glad", "GLFW", "ImGui", "opengl32.lib" }

    pchheader "defpch.h"
    pchsource "build/src/defpch.cpp"

    filter "system:windows" 
      staticruntime "On"
      systemversion "latest"
      system "windows"

      defines { "DEF_WIN" }

    filter { "configurations:Debug" }
      defines { "DEF_DEBUG", "DEBUG" }
      symbols "On"
      kind "ConsoleApp"

    filter { "configurations:Release" }
      defines { "DEF_RELEASE", "NDEBUG" }
      optimize "On"
      kind "ConsoleApp"

      filter { "configurations:Distribution" }
      defines { "DEF_DISTRIBUTION", "NDEBUG" }
      optimize "On"
      kind "WindowedApp"
