IncludeDir = {  --include目录
    ["spdlog"] = "vendor/spdlog/include",
    ["GLFW"] = "vendor/glfw/include",
    ["GLAD"] = "vendor/glad/include",
    ["ImGui"] = "vendor/imgui",
    ["ImGui_Backends"] = "vendor/imgui/backends",
    ["json"] = "vendor/json/include",
}

LibraryDir = {  --lib库目录
    --["mono"] = "%{wks.location}/Dazel/Vender/mono/lib/%{cfg.buildcfg}",
}

Library = { --lib文件
    --["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib",
}