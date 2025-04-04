#pragma once
#include "AUIScreen.h"
#include "PreviewScreen.h"

class CurrentLoadingBar : public AUIScreen
{
public:
    static CurrentLoadingBar* getInstance();
    CurrentLoadingBar();

    void startLoadingFrom(PreviewScreen* source);

private:
    void drawUI() override;

    static CurrentLoadingBar* instance;
    PreviewScreen* sourceScreen = nullptr;

    bool isActive = false;
};