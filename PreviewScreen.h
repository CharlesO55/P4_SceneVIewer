#pragma once
#include "AUIScreen.h"
#include "imgui.h"
#include <glad/glad.h>

class PreviewScreen : public AUIScreen
{
public:
	PreviewScreen(float posX, float posY, int sceneNum);
	~PreviewScreen();

	void updateLoadingProgress(float progress);

private:
	void drawUI() override;
	void loadTexture(const std::string& filePath);

private:
	float posX;
	float posY;

	int sceneNum;

	GLuint textureID;
	int width, height;

	float fakeLoad = 0.0f; // Load tester

	float loadingProgress; 
	bool isLoadingComplete;
};

