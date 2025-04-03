#pragma once
#include "AUIScreen.h"
#include "imgui.h"
#include <glad/glad.h>

class PreviewScreen : public AUIScreen
{
public:
	PreviewScreen();
	~PreviewScreen();

private:
	void drawUI() override;
	void loadTexture(const std::string& filePath);

	GLuint textureID;
	int width, height;

};

