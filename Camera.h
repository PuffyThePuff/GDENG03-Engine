#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	void update(float deltaTime) override;
	Matrix4x4 getViewMatrix();

	void onKeyUp(int key) override;
	void onKeyDown(int key) override;
	void onMouseMove(const Point deltaPos) override;
	void onLeftMouseDown(const Point deltaPos) override;
	void onLeftMouseUp(const Point deltaPos) override;
	void onRightMouseDown(const Point deltaPos) override;
	void onRightMouseUp(const Point deltaPos) override;

	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

private:
	void updateViewMatrix();

	bool mCameraControlsEnabled = false;
};