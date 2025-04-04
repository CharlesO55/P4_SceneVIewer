#include "PreviewScreen.h"
#include <iostream>
#include "imgui.h"
#include "stb_image.h"
#include <glad/glad.h>

#include "src/SceneManager.h"
#include "CurrentLoadingBar.h"

PreviewScreen::PreviewScreen(float posX, float posY, int sceneNum) : AUIScreen("PreviewScreen")
{
    this->posX = posX;
    this->posY = posY;

    this->sceneNum = sceneNum;

    this->textureID = 0;
    this->width = 0;
    this->height = 0;

    this->loadingProgress = 0.0f;
    this->isLoadingComplete = false;

    // Change the image once we have them, we'll just take screenshots of previews
    this->loadTexture("ClientFiles/Scene2/Test.jpg");
}

PreviewScreen::~PreviewScreen() 
{
    std::cout << "Destroying PreviewScreen " << this << std::endl;
    if (textureID) glDeleteTextures(1, &textureID); 
}

void PreviewScreen::changeImage(std::string path)
{
    this->loadTexture(path);
}

void PreviewScreen::updateLoadingProgress(float progress)
{
    this->loadingProgress = progress;
    this->isLoadingComplete = (progress >= 1.0f);
}

float PreviewScreen::getLoadingProgress() const
{
    return this->loadingProgress; 
}

bool PreviewScreen::getLoadingComplete() const
{
    return this->isLoadingComplete;
}

int PreviewScreen::getSceneNum()
{
    return this->sceneNum;
}

void PreviewScreen::drawUI()
{
    char windowTitle[32];
    snprintf(windowTitle, sizeof(windowTitle), "Scene %d", this->sceneNum);

    ImGui::SetNextWindowPos(ImVec2(this->posX, this->posY), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_Always);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize |
                                   ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_NoScrollbar |
                                   ImGuiWindowFlags_NoScrollWithMouse |
                                   ImGuiWindowFlags_NoCollapse;

    ImGui::Begin(windowTitle, nullptr, windowFlags);
    ImGui::PushID(this);

#pragma region Preview Image

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

#pragma endregion

#pragma region Unload Button

    if (this->isLoadingComplete) {
        ImGui::PushID("CloseButton");

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 0.9f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f); 

        ImVec2 closeButtonSize(24, 24);
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - closeButtonSize.x - 8, 20));

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Default bold font 
        if (ImGui::Button("X", closeButtonSize)) {
            std::cout << "Close button clicked" << std::endl;
            SceneManager::instance->UnloadSceneByName("Scene" + std::to_string(sceneNum));

            this->fakeLoad = 0.0f;
            this->loadingProgress = 0.0f;
            this->isLoadingComplete = false;
        }
        ImGui::PopFont();

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }

#pragma endregion


#pragma region Load Button

    const float buttonHeight = ImGui::GetFrameHeightWithSpacing();
    const float progressBarHeight = 20.0f;
    const float spacing = 5.0f;
    const float totalBottomHeight = buttonHeight + spacing;

    ImVec2 bottomAreaStart(0, windowSize.y - totalBottomHeight);
    ImGui::SetCursorPos(bottomAreaStart);

    float availableWidth = windowSize.x;
    float loadButtonWidth = ImGui::CalcTextSize("LOAD SCENE").x + 20.0f;
    float viewButtonWidth = ImGui::CalcTextSize("VIEW SCENE").x + 20.0f;
    float totalButtonsWidth = loadButtonWidth + viewButtonWidth + 10.0f;

    // Center both buttons together
    ImGui::SetCursorPosX((availableWidth - totalButtonsWidth) * 0.5f);

    ImGui::PushID("LoadButton");
    ImVec4 loadButtonColor = ImGui::GetStyle().Colors[ImGuiCol_Button];
    loadButtonColor.w = 0.9f;
    ImGui::PushStyleColor(ImGuiCol_Button, loadButtonColor);

    if (ImGui::Button("LOAD SCENE", ImVec2(loadButtonWidth, 0))) {
        std::cout << "Scene" << sceneNum << " Loaded" << std::endl;
    }
    ImGui::PopStyleColor();
    ImGui::PopID();

    ImGui::SameLine(0.0f, 10.0f);

    ImGui::PushID("ViewButton");
    ImVec4 viewButtonColor = ImGui::GetStyle().Colors[ImGuiCol_Button];
    viewButtonColor = ImVec4(0.2f, 0.7f, 0.2f, 0.9f); // Green color
    ImGui::PushStyleColor(ImGuiCol_Button, viewButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.6f, 0.1f, 1.0f));

    if (ImGui::Button("VIEW SCENE", ImVec2(viewButtonWidth, 0))) {
        std::cout << "Viewing Scene " << sceneNum << std::endl;
        SceneManager::instance->ToggleRenderAll(false);
        SceneManager::instance->SwitchActiveScene("Scene" + std::to_string(sceneNum));
        CurrentLoadingBar::getInstance()->startLoadingFrom(this);
    }

    ImGui::PopStyleColor(3);
    ImGui::PopID();

#pragma endregion

#pragma region Loading Bar

    ImGui::SetCursorPosX((windowSize.x - windowSize.x * 0.8f) * 0.5f);
    
    // Progress bar styling
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 0.9f));
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, 
        this->isLoadingComplete ? 
        ImVec4(0.0f, 1.0f, 0.0f, 1.0f) : // Green when complete
        ImVec4(0.26f, 0.59f, 0.98f, 0.9f)); // Blue while loading
    
    ImGui::ProgressBar(this->loadingProgress, ImVec2(windowSize.x * 0.8f, progressBarHeight), "");
    ImGui::PopStyleColor(2);

    // Centered percentage text
    char progressText[32];
    sprintf_s(progressText, "%.0f%%", this->loadingProgress * 100.0f);
    ImVec2 textPos( (windowSize.x - ImGui::CalcTextSize(progressText).x) * 0.5f,
                     ImGui::GetCursorPosY() - progressBarHeight);
    ImGui::SetCursorPos(textPos);
    ImGui::Text("%s", progressText);

    ImGui::PopID();
    ImGui::End();

#pragma endregion

    // FAKE LOADING - Comment out when not needed
    this->fakeLoad += 0.0001f;

    if (this->fakeLoad >= 1)
        this->fakeLoad = 1;

    this->updateLoadingProgress(this->fakeLoad);
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