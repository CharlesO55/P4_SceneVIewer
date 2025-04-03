#pragma once
#include "AUIScreen.h"
#include "imgui.h"
#include <glad/glad.h>

class PreviewScreen : public AUIScreen
{
public:
	PreviewScreen();
	~PreviewScreen();

	void updateLoadingProgress(float progress);

private:
	void drawUI() override;
	void loadTexture(const std::string& filePath);

	GLuint textureID;
	int width, height;

	float fakeLoad = 0.0f; // Load tester

	float loadingProgress; 
	bool isLoadingComplete;
};

