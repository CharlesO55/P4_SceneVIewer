#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.f) {
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


glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
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
    float x = static_cast<float>(xposIn);
    float y = static_cast<float>(yposIn);

    if (instance->firstMouse)
    {
        instance->lastX = x;
        instance->lastY = y;
        instance->firstMouse = false;
    }

    float xoffset = x - instance->lastX;
    float yoffset = instance->lastY - y; // reversed since y-coordinates go from bottom to top

    instance->lastX = x;
    instance->lastY = y;

    instance->ProcessMouseMovement(xoffset, yoffset);
}

void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    instance->ProcessMouseScroll(static_cast<float>(yoffset));
}