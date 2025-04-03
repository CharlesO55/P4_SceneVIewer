#pragma once
#include "AUIScreen.h"

class ViewAllButton : public AUIScreen
{
public:
    ViewAllButton();
    ~ViewAllButton();

    void drawUI() override;

private:
    const float BUTTON_WIDTH = 150.0f; 
    const float BUTTON_HEIGHT = 60.0f; 

    //Padding from the eges
    const float PADDING_RIGHT = 20.0f;
    const float PADDING_BOTTOM = 20.0f; 
};