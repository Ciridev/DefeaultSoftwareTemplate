workspace "PhysX"
  architecture "x64"
  configurations { "Debug", "Release", "Distribution" }
  startproject "PhysX"

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
  
  project "PhysX"
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

    pchheader "pxpch.h"
    pchsource "build/src/pxpch.cpp"

    filter "system:windows" 
      staticruntime "On"
      systemversion "latest"
      system "windows"

      defines { "PHYSX_WIN" }

    filter { "configurations:Debug" }
      defines { "PHYSX_DEBUG", "DEBUG" }
      symbols "On"
      kind "ConsoleApp"

    filter { "configurations:Release" }
      defines { "PHYSX_RELEASE", "NDEBUG" }
      optimize "On"
      kind "ConsoleApp"

      filter { "configurations:Distribution" }
      defines { "PHYSX_DISTRIBUTION", "NDEBUG" }
      optimize "On"
      kind "WindowedApp"
