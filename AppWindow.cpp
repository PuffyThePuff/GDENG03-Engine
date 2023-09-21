#include "AppWindow.h"
#include "TriangleShape.h"
#include "QuadShape.h"

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain=GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//vertex list[] = 
	//{
	//	//X - Y - Z
	//	{-0.5f, -0.5f, 0.0f},
	//	{-0.5f, 0.5f, 0.0f},
	//	{0.5f, 0.5f, 0.0f},
	//	{0.5f, -0.5f, 0.0f},
	//	{-0.5f, -0.5f, 0.0f}
	//};

	// TriangleShape* newTriangle = new TriangleShape({-0.5f, -0.5f, 0.f}, 0);

	vertex list[18];

	//TODO: put this in a loop
	QuadShape* quad1 = new QuadShape({-1.f, -1.f, 0.f}, 0);
	QuadShape* quad2 = new QuadShape({-1.f, 0.2f, 0.f}, 1);
	QuadShape* quad3 = new QuadShape({0.2f, 0.2f, 0.f}, 2);

	list[0] = quad1->getVertexList()[0];
	list[1] = quad1->getVertexList()[1];
	list[2] = quad1->getVertexList()[2];
	list[3] = quad1->getVertexList()[3];
	list[4] = quad1->getVertexList()[4];
	list[5] = quad2->getVertexList()[0];

	list[6] = quad2->getVertexList()[0];
	list[7] = quad2->getVertexList()[1];
	list[8] = quad2->getVertexList()[2];
	list[9] = quad2->getVertexList()[3];
	list[10] = quad2->getVertexList()[4];
	list[11] = quad3->getVertexList()[0];

	list[12] = quad3->getVertexList()[0];
	list[13] = quad3->getVertexList()[1];
	list[14] = quad3->getVertexList()[2];
	list[15] = quad3->getVertexList()[3];
	list[16] = quad3->getVertexList()[4];
	list[17] = quad3->getVertexList()[0];

	m_vb = GraphicsEngine::get()->createVertexBuffer();

	//TODO: use the loop for this
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	//CLEAR RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		1.f, 0.f,1.f, 1.f);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->setShaders();

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	//DRAW QUADS
	GraphicsEngine::get()->getImmediateDeviceContext()->drawSquareList(m_vb->getSizeVertexList(), 0);

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}
