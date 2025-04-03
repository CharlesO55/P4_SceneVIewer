#include "FPSCounter.h"
#include "imgui.h"

FPSCounter::FPSCounter() : AUIScreen("FPSCounter")
{
    this->lastUpdateTime = std::chrono::steady_clock::now();
}

FPSCounter::~FPSCounter() {}

void FPSCounter::drawUI()
{
    // Update values only every 0.5 seconds
    auto timer = std::chrono::steady_clock::now();
    float timeSinceLastUpdate = std::chrono::duration<float>(timer - this->lastUpdateTime).count();

    if (timeSinceLastUpdate >= 0.5f) {
        ImGuiIO& io = ImGui::GetIO();

        // Cap FPS at 120
        this->cachedFPS = io.Framerate > 120.0f ? 120.0f : io.Framerate;
        this->cachedFPS = io.Framerate; // Turn off to limit fps count to 120
        this->cachedFrameTime = 1000.0f / this->cachedFPS;

        this->lastUpdateTime = timer;
    }

    // Window setup
    const float windowWidth = 180.0f;
    const float windowHeight = 40.0f;
    ImVec2 windowPos(10.0f, ImGui::GetIO().DisplaySize.y - windowHeight - 10.0f);

    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.3f));

    ImGui::Begin("FPS Counter", nullptr, flags);
    {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1f FPS (%.1f ms)", this->cachedFPS,this->cachedFrameTime);
    }
    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}