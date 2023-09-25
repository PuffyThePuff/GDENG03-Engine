#include "AppWindow.h"
#include "TriangleShape.h"
#include "QuadShape.h"
#include <Windows.h>

__declspec(align(16))
struct constant
{
	float m_angle;
};

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

	//vertex list[18];

	////TODO: put this in a loop
	//QuadShape* quad1 = new QuadShape({-1.f, -1.f, 0.f}, 0);
	//QuadShape* quad2 = new QuadShape({-1.f, 0.2f, 0.f}, 1);
	//QuadShape* quad3 = new QuadShape({0.2f, 0.2f, 0.f}, 2);

	//list[0] = quad1->getVertexList()[0];
	//list[1] = quad1->getVertexList()[1];
	//list[2] = quad1->getVertexList()[2];
	//list[3] = quad1->getVertexList()[3];
	//list[4] = quad1->getVertexList()[4];
	//list[5] = quad2->getVertexList()[0];

	//list[6] = quad2->getVertexList()[0];
	//list[7] = quad2->getVertexList()[1];
	//list[8] = quad2->getVertexList()[2];
	//list[9] = quad2->getVertexList()[3];
	//list[10] = quad2->getVertexList()[4];
	//list[11] = quad3->getVertexList()[0];

	//list[12] = quad3->getVertexList()[0];
	//list[13] = quad3->getVertexList()[1];
	//list[14] = quad3->getVertexList()[2];
	//list[15] = quad3->getVertexList()[3];
	//list[16] = quad3->getVertexList()[4];
	//list[17] = quad3->getVertexList()[0];

	vertex list[] = 
	{
		//X - Y - Z
		{{-0.5f, -0.5f, 0.0f}, {-0.32f, -0.11f, 0.0f,}, {1.f, 0.f, 0.f}, {0, 1, 0}}, // POS1
		{{-0.5f, 0.5f, 0.0f}, {-0.11f, 0.78f, 0.0f}, {0.f, 1.f, 0.f}, {0, 1, 1}}, // POS2
		{{0.5f, -0.5f, 0.0f}, {0.75f, -0.73f, 0.0f}, {0.f, 0.f, 1.f}, {1, 0, 0}}, // POS3
		{{0.5f, 0.5f, 0.0f}, {0.88f, 0.77f, 0.0f}, {1.f, 1.f, 0.f}, {0, 0, 1}}
	};

	m_vb=GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f,0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f*m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	//BIND CONSTANT BUFFER TO SHADERS
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
