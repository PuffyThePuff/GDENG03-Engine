#include "AppWindow.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "Cube.h"
#include "Vector3D.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "MathUtils.h"
#include "Matrix4x4.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	EngineTime::initialize();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = getClientWindowRect();

	std::cout << "hwnd: " << this->m_hwnd;
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//initialize skybox color
	this->skyboxColor[0] = 0.3f;
	this->skyboxColor[1] = 1.f;
	this->skyboxColor[2] = 0.5f;

	//create camera object
	Camera* sceneCamera = new Camera("default camera");
	sceneCamera->setPosition(0.f, 0.f, 0.f);
	sceneCamera->setRotation(0.f, 0.f, 0.f);
	SceneCameraManager::getInstance()->setSceneCamera(sceneCamera);

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	//compile basic vertex shader
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->m_vertex_shader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	for (int i = 0; i < 3; i++)
	{
		float x = MathUtils::randomFloat(-0.5f, 0.5f);
		float y = MathUtils::randomFloat(-0.5f, 0.5f);
		float z = MathUtils::randomFloat(-0.5f, 0.5f);
	
		Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
		cubeObject->setAnimSpeed(1.f);
		cubeObject->setPosition(Vector3D(x, y, z));
		cubeObject->setScale(Vector3D(0.25, 0.25, 0.25));
		this->cubeList.push_back(cubeObject);
	}

	graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

	//compile basic pixel shader
	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
	graphEngine->releaseCompiledShader();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplWin32_Init(this->m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirect3DDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());
}

void AppWindow::onUpdate()
{
	ticks += EngineTime::getDeltaTime() * 1.0f;

	InputSystem::getInstance()->update();
	SceneCameraManager::getInstance()->update();

	//set up IMGUI window
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;
	ImGui::Begin("Scene Settings", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(400, 120));
	ImGui::Text("Below are settings for configuring the scene.");
	ImGui::Checkbox("Show Demo Window", &isDemoWindowOpen);
	ImGui::ColorEdit3("Clear Color", this->skyboxColor);
	if (isCubeAnimated) {
		if (ImGui::Button("Pause Animation")) isCubeAnimated = false;
	}
	else if (ImGui::Button("Resume Animation")) isCubeAnimated = true;

	ImGui::End();

	if (isDemoWindowOpen) 
	{
		ImGui::ShowDemoWindow();
	}

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, this->skyboxColor[0], this->skyboxColor[1], this->skyboxColor[2], 1);

	RECT rc = getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	for (int i = 0; i < cubeList.size(); i++)
	{
		if (isCubeAnimated)
		{
			cubeList[i]->update(EngineTime::getDeltaTime());
		}
		cubeList[i]->draw(width, height, m_vertex_shader, m_pixel_shader);
	}

	//render IMGUI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	//m_vertex_buffer->release();
	//m_index_buffer->release();
	//m_constant_buffer->release();

	m_vertex_shader->release();
	m_pixel_shader->release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	InputSystem::destroy();
	SceneCameraManager::destroy();
	GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
	cout << "onkeydown:\n";
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "W pressed\n";
	}
}

void AppWindow::onKeyUp(int key)
{
	cout << "onkeyup:\n";
	if (InputSystem::getInstance()->isKeyUp('W'))
	{
		cout << "W released\n";
	}
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	cout << " mouse moved: " << deltaPos.getX() << ", " << deltaPos.getY() << "\n";
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{

}
