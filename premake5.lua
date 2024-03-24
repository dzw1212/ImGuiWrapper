include "libraries.lua"

workspace "ImGuiWrapper"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    group "vendor"
        include "vendor/GLFW"
        include "vendor/GLAD"
        include "vendor/ImGui"
    group ""

project "ImGuiWrapper"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    defines
    {
        "_CRT_SECURE_NOT_WARNINGS",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGui_Backends}",
        "%{IncludeDir.json}",
    }

    libdirs{}

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"