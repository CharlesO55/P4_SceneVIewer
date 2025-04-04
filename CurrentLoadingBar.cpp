#include "CurrentLoadingBar.h"
#include <iostream>
#include "imgui.h"

CurrentLoadingBar* CurrentLoadingBar::instance = nullptr;
PreviewScreen* CurrentLoadingBar::targetScreen = nullptr;

CurrentLoadingBar* CurrentLoadingBar::getInstance()
{
    if (!instance) {
        instance = new CurrentLoadingBar();
        std::cout << "Creating Current Loading Bar" << std::endl;
    }
    return instance;
}

CurrentLoadingBar::CurrentLoadingBar() : AUIScreen("CurrentLoadingBar") {}

void CurrentLoadingBar::startLoadingFrom(PreviewScreen* source)
{
    this->targetScreen = source;
    this->isActive = true;
}

void CurrentLoadingBar::drawUI()
{
    if (!isActive || !this->targetScreen || this->targetScreen->getLoadingComplete()) {
        isActive = false;
        return;
    }

    // Position at bottom center of screen
    const float barWidth = 400.0f;
    const float barHeight = 30.0f;
    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    ImVec2 barPos((screenSize.x - barWidth) * 0.5f, screenSize.y - barHeight - 20.0f);

    ImGui::SetNextWindowPos(barPos);
    ImGui::SetNextWindowSize(ImVec2(barWidth, barHeight));

    // Transparent window with no decorations
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove |
                            ImGuiWindowFlags_NoScrollbar |
                            ImGuiWindowFlags_NoCollapse |
                            ImGuiWindowFlags_NoBackground |
                            ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("CurrentLoadingBar", nullptr, flags);
    {
        float progress = targetScreen->getLoadingProgress();
        bool complete = targetScreen->getLoadingComplete();
        
        // Loading bar styling
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 0.9f));
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram,
            complete ?
            ImVec4(0.0f, 1.0f, 0.0f, 1.0f) : // Green when complete
            ImVec4(0.26f, 0.59f, 0.98f, 0.9f)); // Blue while loading

        ImGui::ProgressBar(progress, ImVec2(-1, barHeight), "");
        ImGui::PopStyleColor(2);

        // Centered percentage text
        char progressText[32];
        snprintf(progressText, sizeof(progressText), "%.0f%%", progress * 100.0f);
        ImVec2 textSize = ImGui::CalcTextSize(progressText);
        ImVec2 textPos(
            (barWidth - textSize.x) * 0.5f,
            (barHeight - textSize.y) * 0.5f
        );
        ImGui::SetCursorPos(textPos);
        ImGui::Text("%s", progressText);
    }
    ImGui::End();
}