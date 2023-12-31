#include "Vector3D.h"

Vector3D::Vector3D()
{

}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(const Vector3D* vector)
{
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
}

Vector3D::Vect Vector3D::getValues() const
{
	Vect vect = {};
	vect.x = this->x;
	vect.y = this->y;
	vect.z = this->z;

	return vect;
}

Vector3D Vector3D::lerp(const Vector3D start, const Vector3D end, float delta)
{
	Vector3D v;
	v.x = start.x * (1.0f - delta) + end.x * (delta);
	v.y = start.y * (1.0f - delta) + end.y * (delta);
	v.z = start.z * (1.0f - delta) + end.z * (delta);

	return v;
}

Vector3D Vector3D::ones()
{
	return Vector3D(1.0f, 1.0f, 1.0f);
}

Vector3D Vector3D::zeros()
{
	return Vector3D(0.0f, 0.0f, 0.0f);
}

void Vector3D::operator =(const Vector3D& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector3D::operator +=(const Vector3D& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

Vector3D Vector3D::operator +(Vector3D vector)
{
	return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D Vector3D::operator *(float scalar)
{
	return Vector3D(scalar * x, scalar * y, scalar * z);
}

Vector3D::~Vector3D()
{
}
