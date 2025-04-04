#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <thread>
#include <vector>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "FileServer.h"
#include "FileClient.h"
#include "UIManager.h"
 
//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"


#include "src/Shader.h"
#include "src/Camera.h"
#include "src/Model.h"



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
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

    // GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // STBI IMG
    stbi_set_flip_vertically_on_load(true);
    // OPENGL AGAIN
    glEnable(GL_DEPTH_TEST);


    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();  
    ImGui::StyleColorsDark();

    UIManager::initialize(); 

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // SHADER
    Shader shader("Shader/shaderModel.vert", "Shader/shaderModel.frag");

    // CAMERA
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.InitCallbacks(window);
    
    
    // SCENE MODELS
    // SAMPLE.. [TO DO] Make a manager
    std::vector<Model> models;
    models.push_back(Model("ClientFiles/Scene2/armadillo.obj", glm::vec3(5, 0, 5)));
    models.push_back(Model("ClientFiles/Scene1/Cylinder.obj", glm::vec3(0, -5, -5)));




    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Event loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        // RENDER SCENE
        camera.CheckMoveInput(window, deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        camera.SetViewProjectMatrix(shader, (float)UIManager::WINDOW_WIDTH / (float)UIManager::WINDOW_HEIGHT);

        for (Model& m : models) {
            m.Draw(shader);
        }


        // UI
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