#pragma once
#include <vector>

#include "Cube.h"
#include "InputListener.h"
#include "Window.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "Camera.h"
#include "SceneCameraManager.h"
#include "UIManager.h"
#include "GameObjectManager.h"

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;


	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point deltaPos);

	virtual void onLeftMouseDown(const Point deltaPos);
	virtual void onLeftMouseUp(const Point deltaPos);

	virtual void onRightMouseDown(const Point deltaPos);
	virtual void onRightMouseUp(const Point deltaPos);
private:
	std::vector<Cube*> cubeList;

	float ticks = 0.0f;

	SwapChain* m_swap_chain;
	VertexBuffer* m_vertex_buffer;
	ConstantBuffer* m_constant_buffer;
	IndexBuffer* m_index_buffer;

	VertexShader* m_vertex_shader;
	PixelShader* m_pixel_shader;

	bool isCubeAnimated = true;
	bool isDemoWindowOpen = false;
	float skyboxColor[3];
};

