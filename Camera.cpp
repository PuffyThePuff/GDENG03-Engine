#include "Camera.h"

Camera::Camera(std::string name) : AGameObject::AGameObject(name)
{
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	if (mCameraControlsEnabled)
	{
		Vector3D newPosition = this->getLocalPosition();
		float movementSpeed = 5.f;
		float movementScalar;

		if (InputSystem::getInstance()->isKeyDown('W'))
		{
			movementScalar = deltaTime * movementSpeed * 1.f;
			newPosition += (this->localMatrix.getZDirection() * movementScalar);
			this->setPosition(newPosition);

			updateViewMatrix();
		}

		else if (InputSystem::getInstance()->isKeyDown('S'))
		{
			movementScalar = deltaTime * movementSpeed * -1.f;
			newPosition += (this->localMatrix.getZDirection() * movementScalar);
			this->setPosition(newPosition);

			updateViewMatrix();
		}

		else if (InputSystem::getInstance()->isKeyDown('D'))
		{
			movementScalar = deltaTime * movementSpeed * 1.f;
			newPosition += (this->localMatrix.getXDirection() * movementScalar);
			this->setPosition(newPosition);

			updateViewMatrix();
		}

		else if (InputSystem::getInstance()->isKeyDown('A'))
		{
			movementScalar = deltaTime * movementSpeed * -1.f;
			newPosition += (this->localMatrix.getXDirection() * movementScalar);
			this->setPosition(newPosition);

			updateViewMatrix();
		}
	}
}

Matrix4x4 Camera::getViewMatrix()
{
	Matrix4x4 viewMatrix = this->localMatrix;
	viewMatrix.inverse();
	return viewMatrix;
}

void Camera::onKeyUp(int key)
{

}

void Camera::onKeyDown(int key)
{
	
}

void Camera::onMouseMove(const Point deltaPos)
{
	Vector3D newRotation = this->getLocalRotation();

	newRotation.y += (float)deltaPos.getX() * 0.01f;
	newRotation.x += (float)deltaPos.getY() * 0.01f;

	this->setRotation(newRotation);

	updateViewMatrix();
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
	std::cout << "Left mouse button pressed" << std::endl;
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
	std::cout << "Left mouse button released" << std::endl;
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	std::cout << "Right mouse button pressed" << std::endl;

	mCameraControlsEnabled = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	std::cout << "Right mouse button released" << std::endl;
	
	mCameraControlsEnabled = false;
}

void Camera::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCamMatrix;
	Vector3D localRotation = this->getLocalRotation();
	
	worldCamMatrix.setIdentity();
	worldCamMatrix.rotate(0, localRotation.x);
	worldCamMatrix.rotate(1, localRotation.y);
	worldCamMatrix.rotate(2, localRotation.z);
	worldCamMatrix.translate(this->getLocalPosition());

	this->localMatrix = worldCamMatrix;
}
