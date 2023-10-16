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
	Vector3D newRotation = this->getLocalRotation();
	switch(key)
	{
		case(VK_UP):
			newRotation.y += 20;
			this->setRotation(newRotation);
			
			updateViewMatrix();
			break;
		case(VK_DOWN):
			newRotation.y -= 20;
			this->setRotation(newRotation);

			updateViewMatrix();
			break;
		case(VK_LEFT):
			newRotation.x += 20;
			this->setRotation(newRotation);

			updateViewMatrix();
			break;
		case(VK_RIGHT):
			newRotation.x += 20;
			this->setRotation(newRotation);

			updateViewMatrix();
			break;
		default:
			break;
	}
}

void Camera::onMouseMove(const Point deltaPos)
{
	Vector3D newRotation = this->getLocalRotation();

	newRotation.y += (float)deltaPos.getX() * 0.1f;
	newRotation.x += (float)deltaPos.getY() * 0.1f;

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
	
	mCameraControlsEnabled = true;
}

void Camera::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCamMatrix;
	Vector3D localRotation = this->getLocalRotation();

	//std::cout << "Rotation: " << this->getLocalRotation().x << " " << this->getLocalRotation().y << " " << this->getLocalRotation().z << std::endl;
	worldCamMatrix.setIdentity();
	worldCamMatrix.rotate(0, localRotation.x);
	worldCamMatrix.rotate(1, localRotation.y);
	worldCamMatrix.rotate(2, localRotation.z);
	worldCamMatrix.translate(this->getLocalPosition());

	this->localMatrix = worldCamMatrix;

	//for(int i=0;i<4;i++)
	//{
	//	for(int j=0;j<4;j++)
	//	{
	//		std::cout<<this->localMatrix.matrix[i][j];
	//	}
	//	std::cout<<std::endl;
	//}

	std::cout << "View Matrix updated" << std::endl;
}
