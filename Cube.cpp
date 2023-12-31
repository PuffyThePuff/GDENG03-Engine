#include "Cube.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	//create buffers for drawing. vertex data that needs to be drawn are temporarily placed here.
	Vertex quadList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(0,0,1), Vector3D(1,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
		{Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,0,1), Vector3D(1,0,0) },
	};

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(indexList, ARRAYSIZE(indexList));

	//create constant buffer
	CBData cbData = {};
	cbData.time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));

	InputSystem::getInstance()->addListener(this);
}

Cube::~Cube()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	this->constantBuffer->release();
	AGameObject::~AGameObject();

	InputSystem::getInstance()->removeListener(this);
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;
}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	CBData cbData = {};
	cbData.time = this->ticks * this->speed;
	
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getValues().z);
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getValues().x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getValues().y);
	// Combine x-y-z rotation matrices into one.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));
	//Scale --> Rotate --> Translate as recommended order.
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	cbData.worldMatrix = allMatrix;

	cbData.viewMatrix = SceneCameraManager::getInstance()->getSceneCameraViewMatrix();
	cbData.projMatrix.setPerspectiveFovLH(1.57f, (float)width / (float)height, 0.1f, 100.f);

	// set shaders
	deviceContext->setVertexShader(vertexShader);
	deviceContext->setPixelShader(pixelShader);

	this->constantBuffer->update(deviceContext, &cbData);
	deviceContext->setConstantBuffer(vertexShader, this->constantBuffer);
	deviceContext->setConstantBuffer(pixelShader, this->constantBuffer);

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getIndexSize(), 0, 0);
	//graphEngine->getSwapChain()->present(true); // we do not present immediately. We draw all objects first, before displaying
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

void Cube::onKeyUp(int key)
{
	
}

void Cube::onKeyDown(int key)
{
	Vector3D pos = this->getLocalPosition();
	if (key == 'I')
	{
		this->setPosition(pos.x, pos.y + 1.f, pos.z);
	}
	if (key == 'K')
	{
		this->setPosition(pos.x, pos.y - 1.f, pos.z);
	}
	if (key == 'J')
	{
		this->setPosition(pos.x + 1.f, pos.y, pos.z);
	}
	if (key == 'L')
	{
		this->setPosition(pos.x - 1.f, pos.y, pos.z);
	}
}

void Cube::onMouseMove(Point delta_position)
{
}

void Cube::onLeftMouseDown(Point mouse_position)
{
}

void Cube::onLeftMouseUp(Point mouse_position)
{
}

void Cube::onRightMouseDown(Point mouse_position)
{
}

void Cube::onRightMouseUp(Point mouse_position)
{
}
