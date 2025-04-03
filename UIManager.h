#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "AUIScreen.h"

class UINames {
public:
	const String PREVIEW_SCREEN = "PREVIEW_SCREEN";
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

