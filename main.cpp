#include "FileServer.h"
#include "FileClient.h"
#include "UIManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
 
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"




int main()
{
    // Async run
    FileServer fServer;
    fServer.start();
    
    //Wait for server to startup
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    FileClient::runClient();
    
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Defines the type for the window output screen
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(UIManager::WINDOW_WIDTH, UIManager::WINDOW_HEIGHT, "GDPARCM P4 - GALURA & ONG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }
    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();  
    ImGui::StyleColorsDark();

    UIManager::initialize(); 

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Event loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        UIManager::getInstance()->drawAllUI();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    UIManager::destroy();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}