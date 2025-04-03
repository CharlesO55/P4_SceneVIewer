#include "PreviewScreen.h"
#include <iostream>
#include "imgui.h"
#include "stb_image.h"
#include <glad/glad.h>

PreviewScreen::PreviewScreen() : AUIScreen("PreviewScreen") 
{
    this->textureID = 0;
    this->width = 0;
    this->height = 0;
    this->loadTexture("ClientFiles/Scene2/Test.jpg");
}

PreviewScreen::~PreviewScreen() 
{
    if (textureID) glDeleteTextures(1, &textureID); 
}

void PreviewScreen::drawUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_NoScrollbar |
                                   ImGuiWindowFlags_NoScrollWithMouse |
                                   ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Scene 2", nullptr, windowFlags);

    ImVec2 windowSize = ImGui::GetContentRegionAvail();

    if (textureID != 0) {
        float aspect_ratio = static_cast<float>(height) / width;

        float display_width = windowSize.x;
        float display_height = display_width * aspect_ratio;

        if (display_height > windowSize.y) {
            display_height = windowSize.y;
            display_width = display_height / aspect_ratio;
        }

        ImGui::Image((ImTextureID)(intptr_t)textureID, ImVec2(display_width, display_height));
    }

    else 
        ImGui::Text("Failed to load image.");

    ImGui::SetCursorPosY(windowSize.y - ImGui::GetFrameHeightWithSpacing()); 
    ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize("LOAD SCENE").x) * 0.5f); // Center horizontally

    ImVec4 buttonColor = ImGui::GetStyle().Colors[ImGuiCol_Button];
    buttonColor.w = 0.9f;
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);

    if (ImGui::Button("LOAD SCENE")) {
        // Add loading functionalities here
        std::cout << "Button Clicked" << std::endl;
    }

    ImGui::PopStyleColor();

    ImGui::End();
}

void PreviewScreen::loadTexture(const std::string& filePath) {
    stbi_set_flip_vertically_on_load(false);
    int nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else {
        printf("FAILED TO LOAD: %s\n", filePath.c_str());
        textureID = 0;
    }
}