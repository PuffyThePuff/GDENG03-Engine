#include "Plane.h"
#include "GraphicsEngine.h"

Plane::Plane(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	Vertex quadList[] = {
		//X, Y, Z
		{Vector3D(-0.5f, 0.f, 0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
		{Vector3D(0.5f,0.f,0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
		{Vector3D(-0.5f,0.f,-0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
		{Vector3D(0.5f,0.f,-0.5f),     Vector3D(0,0,1), Vector3D(1,0,0) },
	};

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
	{
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
	};
	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(indexList, ARRAYSIZE(indexList));

	//create constant buffer
	CBData cbData = {};
	cbData.time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));
}

Plane::~Plane()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	this->constantBuffer->release();
	AGameObject::~AGameObject();
}

void Plane::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;
}

void Plane::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	CBData cbData = {};
	cbData.time = this->ticks;

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