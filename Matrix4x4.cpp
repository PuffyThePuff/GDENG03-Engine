#include "Matrix4x4.h"


Matrix4x4::Matrix4x4()
{
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::setIdentity()
{
	//set array as zeros
	this->matrixInitialize();
	this->matrix[0][0] = 1;
	this->matrix[1][1] = 1;
	this->matrix[2][2] = 1;
	this->matrix[3][3] = 1;
}

void Matrix4x4::setTranslation(const Vector3D translation)
{
	this->setIdentity();
	Vector3D::Vect vect = translation.getValues();
	this->matrix[3][0] = vect.x;
	this->matrix[3][1] = vect.y;
	this->matrix[3][2] = vect.z;
}

void Matrix4x4::setScale(const Vector3D scale)
{
	this->setIdentity();
	Vector3D::Vect vect = scale.getValues();
	this->matrix[0][0] = vect.x;
	this->matrix[1][1] = vect.y;
	this->matrix[2][2] = vect.z;
}

void Matrix4x4::setRotationX(float x)
{
	this->setIdentity();
	this->matrix[1][1] = cos(x);
	this->matrix[1][2] = sin(x);
	this->matrix[2][1] = -sin(x);
	this->matrix[2][2] = cos(x);
}

void Matrix4x4::setRotationY(float y)
{
	this->setIdentity();
	this->matrix[0][0] = cos(y);
	this->matrix[0][2] = -sin(y);
	this->matrix[2][0] = sin(y);
	this->matrix[2][2] = cos(y);
}


void Matrix4x4::setRotationZ(float z)
{
	this->setIdentity();
	this->matrix[0][0] = cos(z);
	this->matrix[0][1] = sin(z);
	this->matrix[1][0] = -sin(z);
	this->matrix[1][1] = cos(z);
}

float Matrix4x4::getDeterminant()
{
	Vector4D minor, v1, v2, v3;
	float det;

	v1 = Vector4D(this->matrix[0][0], this->matrix[1][0], this->matrix[2][0], this->matrix[3][0]);
	v2 = Vector4D(this->matrix[0][1], this->matrix[1][1], this->matrix[2][1], this->matrix[3][1]);
	v3 = Vector4D(this->matrix[0][2], this->matrix[1][2], this->matrix[2][2], this->matrix[3][2]);
	
	minor.cross(v1, v2, v3);
	det = -(this->matrix[0][3] * minor.m_x + this->matrix[1][3] * minor.m_y + this->matrix[2][3] * minor.m_z + this->matrix[3][3] * minor.m_w);

	return det;
}

void Matrix4x4::setPerspectiveFovLH(float fov, float aspect, float zNear, float zFar)
{
	float yScale = 1.0f / tan(fov / 2.0f);
	float xScale = yScale / aspect;

	this->matrix[0][0] = xScale;
	this->matrix[1][1] = yScale;
	this->matrix[2][2] = zFar / (zFar - zNear);
	this->matrix[2][3] = 1.f;
	this->matrix[3][2] = (-zNear * zFar) / (zFar - zNear);
}

void Matrix4x4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	this->setIdentity();
	this->matrix[0][0] = 2.0f / width;
	this->matrix[1][1] = 2.0f / height;
	this->matrix[2][2] = 1.0f / (far_plane - near_plane);
	this->matrix[3][2] = -(near_plane / (far_plane - near_plane));
}

Matrix4x4 Matrix4x4::multiplyTo(Matrix4x4 matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.matrix[i][j] =
				this->matrix[i][0] * matrix.matrix[0][j] + this->matrix[i][1] * matrix.matrix[1][j] +
				this->matrix[i][2] * matrix.matrix[2][j] + this->matrix[i][3] * matrix.matrix[3][j];
		}
	}

	return out;
}

void Matrix4x4::inverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4D v, vec[3];
	float det = 0.0f;

	det = this->getDeterminant();
	if (!det) return;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].m_x = (this->matrix[j][0]);
				vec[a].m_y = (this->matrix[j][1]);
				vec[a].m_z = (this->matrix[j][2]);
				vec[a].m_w = (this->matrix[j][3]);
			}
		}
		v.cross(vec[0], vec[1], vec[2]);

		out.matrix[0][i] = pow(-1.0f, i) * v.m_x / det;
		out.matrix[1][i] = pow(-1.0f, i) * v.m_y / det;
		out.matrix[2][i] = pow(-1.0f, i) * v.m_z / det;
		out.matrix[3][i] = pow(-1.0f, i) * v.m_w / det;
	}

	this->setMatrix(out);
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.matrix[i][j] =
				this->matrix[i][0] * matrix.matrix[0][j] + this->matrix[i][1] * matrix.matrix[1][j] +
				this->matrix[i][2] * matrix.matrix[2][j] + this->matrix[i][3] * matrix.matrix[3][j];
		}
	}

	::memcpy(this->matrix, matrix.matrix, sizeof(float) * 16);
}

void Matrix4x4::scale(const Vector3D& scale_vector)
{
	Matrix4x4 scaleMatrix;
	scaleMatrix.setScale(scale_vector);
	*this *= scaleMatrix;
}

void Matrix4x4::translate(float delta_x, float delta_y, float delta_z)
{
	Matrix4x4 translator;
	translator.setTranslation(Vector3D(delta_x, delta_y, delta_z));
	*this *= translator;
}

void Matrix4x4::translate(const Vector3D& translate_vector)
{
	Matrix4x4 translator;
	translator.setTranslation(translate_vector);
	*this *= translator;
}

void Matrix4x4::rotate(int axisOfRotation, float theta)
{
	Matrix4x4 rotationMatrix;
	switch (axisOfRotation)
	{
		case 0:
			rotationMatrix.setIdentity();
			rotationMatrix.setRotationX(theta);
			break;
		case 1:
			rotationMatrix.setIdentity();
			rotationMatrix.setRotationY(theta);
			break;
		case 2:
			rotationMatrix.setIdentity();
			rotationMatrix.setRotationZ(theta);
			break;
		default:
			rotationMatrix.setIdentity();
	}

	*this *= rotationMatrix;
}

Vector3D Matrix4x4::getZDirection()
{
	return Vector3D(this->matrix[2][0], this->matrix[2][1], this->matrix[2][2]);
}

Vector3D Matrix4x4::getXDirection()
{
	return Vector3D(this->matrix[0][0], this->matrix[0][1], this->matrix[0][2]);
}

Vector3D Matrix4x4::getTranslation()
{
	return Vector3D(this->matrix[3][0], this->matrix[3][1], this->matrix[3][2]);
}

void Matrix4x4::setMatrix(const Matrix4x4& matrix)
{
	::memcpy(this->matrix, matrix.matrix, sizeof(float) * 16);
}

void Matrix4x4::debugPrint()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void Matrix4x4::matrixInitialize()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->matrix[i][j] = 0.0f;
		}
	}
}