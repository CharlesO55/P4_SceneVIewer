#pragma once
#include "AUIScreen.h"
#include "imgui.h"

class PreviewScreen : public AUIScreen
{
public:
	PreviewScreen();
	~PreviewScreen();

private:
	void drawUI() override;
};

