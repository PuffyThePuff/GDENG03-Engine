#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"
#include <iostream>

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();
	void setIdentity();
	void setTranslation(const Vector3D translation);
	void setScale(const Vector3D scale);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);
	float getDeterminant();
	void setPerspectiveFovLH(float fov, float aspect, float zNear, float zFar);
	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	Matrix4x4 multiplyTo(Matrix4x4 matrix);
	void inverse();
	void operator *= (const Matrix4x4& matrix);

	void scale(const Vector3D& scale_vector);
	void translate(float delta_x, float delta_y, float delta_z);
	void translate(const Vector3D& translate_vector);
	void rotate(int axisOfRotation, float theta);

	Vector3D getZDirection();
	Vector3D getXDirection();
	Vector3D getTranslation();

	void setMatrix(const Matrix4x4& matrix);

	void debugPrint();

private:
	void matrixInitialize();

	float matrix[4][4] = {};
};