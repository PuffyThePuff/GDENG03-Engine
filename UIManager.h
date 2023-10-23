#pragma once
#include "AUIScreen.h"
#include "GraphicsEngine.h"

#include <vector>
#include <unordered_map>
#include <Windows.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};				//private copy constructor
	UIManager& operator=(UIManager const&) {}	//private assignment operator
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};