#include "PreviewScreen.h"
#include "imgui.h"

PreviewScreen::PreviewScreen() : AUIScreen("PreviewScreen") {}
PreviewScreen::~PreviewScreen() {}

void PreviewScreen::drawUI()
{
    // Set the position to the top left
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Always);

    ImGui::Begin("Scene 2", 0);

    ImGui::Text("Hello, ImGui!");
    ImGui::Text("This is a UI on the top left.");

    ImGui::End();
}