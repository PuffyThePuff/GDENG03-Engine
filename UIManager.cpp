#include "UIManager.h"
#include "GraphicsEngine.h"
#include "InspectorWindow.h"
#include "Profiler.h"
#include "SceneOutliner.h"
#include "Toolbar.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	for (auto& i : sharedInstance->uiList)
	{
		delete i;
	}

	ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto& i : this->uiList)
	{
		i->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirect3DDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

	Toolbar* toolbar = new Toolbar("Toolbar");
    uiList.push_back(toolbar);

    SceneOutliner* outliner = new SceneOutliner("Scene Outliner");
    uiList.push_back(outliner);

    InspectorWindow* inspector = new InspectorWindow("Inspector Window");
    uiList.push_back(inspector);

    Profiler* profiler = new Profiler("Engine Profiler");
    uiList.push_back(profiler);
}

UIManager::~UIManager()
{
	delete sharedInstance;
}
