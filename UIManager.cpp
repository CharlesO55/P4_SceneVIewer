#include "UIManager.h"
#include "PreviewScreen.h"
#include "ViewAllButton.h"
#include "FPSCounter.h"
#include "CurrentLoadingBar.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize()
{
	sharedInstance = new UIManager();
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	for (int i = 0; i < this->uiList.size(); i++) {
		this->uiList[i]->drawUI();
	}
}

UIManager::UIManager()
{
	//populate UI table
	UINames uiNames;
	CurrentLoadingBar* curLoad = new CurrentLoadingBar();
	this->uiTable[uiNames.CURRENT_LOADING] = curLoad;
	this->uiList.push_back(curLoad);

	PreviewScreen* previewScreen1 = new PreviewScreen(10, 10, 1);
	previewScreen1->changeImage("ClientFiles/Scene2/AssembledSample.png");
	this->uiTable[uiNames.PREVIEW_SCREEN_1] = previewScreen1;
	this->uiList.push_back(previewScreen1);
	
	PreviewScreen* previewScreen2 = new PreviewScreen(370, 10, 2);
	this->uiTable[uiNames.PREVIEW_SCREEN_2] = previewScreen2;
	this->uiList.push_back(previewScreen2);

	PreviewScreen* previewScreen3 = new PreviewScreen(730, 10, 3);
	this->uiTable[uiNames.PREVIEW_SCREEN_3] = previewScreen3;
	this->uiList.push_back(previewScreen3);
	
	PreviewScreen* previewScreen4 = new PreviewScreen(1090, 10, 4);
	this->uiTable[uiNames.PREVIEW_SCREEN_4] = previewScreen4;
	this->uiList.push_back(previewScreen4);
	
	PreviewScreen* previewScreen5 = new PreviewScreen(1450, 10, 5);
	this->uiTable[uiNames.PREVIEW_SCREEN_5] = previewScreen5;
	this->uiList.push_back(previewScreen5);

	ViewAllButton* VAButton = new ViewAllButton();
	this->uiTable[uiNames.VIEW_ALL_BUTTON] = VAButton;
	this->uiList.push_back(VAButton);
	
	FPSCounter* fpsCounter = new FPSCounter();
	this->uiTable[uiNames.FPS_COUNTER] = fpsCounter;
	this->uiList.push_back(fpsCounter);

	/*
	ChatScreen* chatScreen = new ChatScreen();
	this->uiTable[uiNames.CHAT_SCREEN] = chatScreen;
	this->uiList.push_back(chatScreen);*/
}

UIManager::~UIManager()
{
}
