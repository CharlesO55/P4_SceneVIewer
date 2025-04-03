#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "AUIScreen.h"

class UINames {
public:
	const String PREVIEW_SCREEN_1 = "PREVIEW_SCREEN_1";
	const String PREVIEW_SCREEN_2 = "PREVIEW_SCREEN_2";
	const String PREVIEW_SCREEN_3 = "PREVIEW_SCREEN_3";
	const String PREVIEW_SCREEN_4 = "PREVIEW_SCREEN_4";
	const String PREVIEW_SCREEN_5 = "PREVIEW_SCREEN_5";
	const String VIEW_ALL_BUTTON = "VIEW_ALL_BUTTON";
	const String FPS_COUNTER = "FPS_COUNTER";
};


class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize();
	static void destroy();

	void drawAllUI();

	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

private:
	UIManager();
	~UIManager();
	UIManager(UIManager const&) {};             // copy constructor is private
	UIManager& operator=(UIManager const&) {};  // assignment operator is private*/
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};

