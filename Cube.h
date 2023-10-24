#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "InputSystem.h"
#include "SceneCameraManager.h"

class Cube: public AGameObject, public InputListener
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);

	void onKeyUp(int key) override;
	void onKeyDown(int key) override;

	void onMouseMove(Point delta_position) override;
	void onLeftMouseDown(Point mouse_position) override;
	void onLeftMouseUp(Point mouse_position) override;
	void onRightMouseDown(Point mouse_position) override;
	void onRightMouseUp(Point mouse_position) override;

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};

