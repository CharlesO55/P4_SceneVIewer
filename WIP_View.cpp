#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/Shader.h"
#include "src/Camera.h"
#include "src/Model.h"

#include <iostream>

#include "UIManager.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(UIManager::WINDOW_WIDTH, UIManager::WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);






    Shader shader("Shader/shaderModel.vert", "Shader/shaderModel.frag");

    // Models
    std::vector<Model> models;
    models.push_back(Model("resources/cow.obj", glm::vec3(5, 0, 5)));
    models.push_back(Model("ClientFiles/Scene1/Cylinder.obj", glm::vec3(0, -5, -5)));
    
    // Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.InitCallbacks(window);
    

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
        camera.CheckMoveInput(window, deltaTime);

        // render
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        
        camera.SetViewProjectMatrix(shader, (float)UIManager::WINDOW_WIDTH / (float)UIManager::WINDOW_HEIGHT);
        
        for (Model& m : models) {
            m.Draw(shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    return 0;
}