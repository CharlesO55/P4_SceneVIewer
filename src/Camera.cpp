#include "Camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Camera* Camera::instance = nullptr;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(15), MouseSensitivity(0.1f), Zoom(45.f) {
    std::cout << "[CAMERA] Create" << std::endl;

    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();

    Camera::instance = this;
}

void Camera::InitCallbacks(GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    lastX = width / 2.0f;
    lastY = height / 2.0f;

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
}


void Camera::SetViewProjectMatrix(Shader& shader, float aspectRatio) {
    glm::mat4 projection = glm::perspective(glm::radians(this->Zoom), aspectRatio, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(Position, Position + Front, Up);//GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

}

void Camera::CheckMoveInput(GLFWwindow* window, float deltaTime) {
    // Too tired to make another listener so just terminate here
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Camera::instance->ProcessKeyboard(Camera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Camera::instance->ProcessKeyboard(Camera::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Camera::instance->ProcessKeyboard(Camera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Camera::instance->ProcessKeyboard(Camera::RIGHT, deltaTime);
}



void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}


void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}


void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    // Forward event to ImGui
    ImGui_ImplGlfw_CursorPosCallback(window, xposIn, yposIn);

    if (ImGui::GetIO().WantCaptureMouse)
        return;

    // Check if the right mouse button is not pressed
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        instance->firstMouse = true; 
        return;
    }

    // Right mouse button is pressed, hide cursor and handle movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float x = static_cast<float>(xposIn);
    float y = static_cast<float>(yposIn);

    if (instance->firstMouse) {
        instance->lastX = x;
        instance->lastY = y;
        instance->firstMouse = false;
    }

    float xoffset = x - instance->lastX;
    float yoffset = instance->lastY - y; // Reversed since y-coordinates go from bottom to top

    instance->lastX = x;
    instance->lastY = y;

    instance->ProcessMouseMovement(xoffset, yoffset);
}

void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    // Forward event to ImGui
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

    if (ImGui::GetIO().WantCaptureMouse)
        return;

    instance->ProcessMouseScroll(static_cast<float>(yoffset));
}