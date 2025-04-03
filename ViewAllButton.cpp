#include "ViewAllButton.h"
#include "imgui.h"
#include "UIManager.h" 

#include <iostream>

ViewAllButton::ViewAllButton() : AUIScreen("ViewAllButton") {}
ViewAllButton::~ViewAllButton() {}

void ViewAllButton::drawUI()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoScrollbar |
                                    ImGuiWindowFlags_NoScrollWithMouse |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoBackground |
                                    ImGuiWindowFlags_NoSavedSettings;

    ImVec2 window_size = ImGui::GetIO().DisplaySize;
    ImVec2 window_pos(window_size.x - BUTTON_WIDTH - PADDING_RIGHT,
                      window_size.y - BUTTON_HEIGHT - PADDING_BOTTOM);

    ImGui::SetNextWindowPos(window_pos);
    ImGui::SetNextWindowSize(ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT));

    ImGui::Begin("ViewAllButtonWindow", nullptr, window_flags);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.5f, 0.8f, 1.0f)); 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.6f, 0.9f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.4f, 0.7f, 1.0f));

    if (ImGui::Button("VIEW ALL", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y)))
    {
        std::cout << "View All Pressed!" << std::endl;
    }

    ImGui::PopStyleColor(3);
    ImGui::End();
}