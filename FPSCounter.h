#pragma once
#include "AUIScreen.h"
#include <chrono>

class FPSCounter : public AUIScreen
{
public:
    FPSCounter();
    ~FPSCounter();

private:
    void drawUI() override;

private:
    std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime;
    float cachedFPS = 0.0f;
    float cachedFrameTime = 0.0f;
};