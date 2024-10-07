#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h> 

#include "Base/Log.h"

#include "Base/Color.h"
#include "Widget/WidgetFactory.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>

ImFont* g_Font = nullptr;
GLFWwindow* g_Window = nullptr;

std::shared_ptr<Window> g_testWindow;

static void Prepare()
{
    g_testWindow = std::dynamic_pointer_cast<Window>(WidgetFactory::CreateWidget<Window>("Test Window"));
    auto text = std::dynamic_pointer_cast<Text>(WidgetFactory::CreateWidget<Text>("Hello World", eTextFlags_Color));
    text->SetColor(Color(255, 0, 0));
    g_testWindow->AddChild(text);
    auto button = std::dynamic_pointer_cast<Button>(WidgetFactory::CreateWidget<Button>("Click Me"));
    button->SetPivot(0.5, 0.5);
    button->SetAnchor(0.5, 0.5);
    g_testWindow->AddChild(button);

    //Json data;
    //g_testWindow->Serialize(data);
    //
    //std::ofstream uiFile("ui.json");
    //uiFile << data.dump(4);

    //std::ifstream uiFile("ui.json");
    //Json data;
    //uiFile >> data;
    //g_testWindow = std::dynamic_pointer_cast<Window>(WidgetFactory::CreateWidget<Window>());
    //g_testWindow->Deserialize(data);
}

static void Draw()
{
    g_testWindow->Draw();
}

static void glfw_error_callback(int error, const char* description)
{
    Log::Error("GLFW Error code={}, des={}", error, description);
}

static bool Init()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return false;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    g_Window = glfwCreateWindow(1920, 1080, "ImGui Wrapper", nullptr, nullptr);
    if (!g_Window)
        return false;

    glfwMakeContextCurrent(g_Window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(g_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Font
    io.Fonts->AddFontDefault();
    g_Font = io.Fonts->AddFontFromFileTTF("./asset/font/simhei.ttf", 32.f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    if (!g_Font)
        return false;

    return true;
}

static void CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(g_Window);
    glfwTerminate();
}

static void Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::PushFont(g_Font);

    Draw();

    ImGui::PopFont();

    ImVec4 clear_color = ImVec4(56.f / 255.f, 56.f / 255.f, 56.f / 255.f, 1.00f);
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(g_Window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static void Loop()
{
    while (!glfwWindowShouldClose(g_Window))
    {
        auto& io = ImGui::GetIO();
        io.WantCaptureMouse = true;
        io.WantCaptureKeyboard = true;

        glfwPollEvents();
        
        Render();

        glfwSwapBuffers(g_Window);
    }
}

int main()
{
    if (!Init())
    {
        Log::Error("Init failed");
        return EXIT_FAILURE;
    }
    Prepare();
    Loop();
    CleanUp();
    return EXIT_SUCCESS;
}