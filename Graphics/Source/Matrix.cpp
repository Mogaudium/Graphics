#include <math.h>
#include "Matrix.h"

#define PI 3.1415926535897932384626433832795

//Matrix methods implementation

const Matrix  Matrix::operator* (const Matrix& other) const
{
	Matrix result;

	result.MatrixSetup(0, 0, GetMatrix(0, 0) * other.GetMatrix(0, 0) + GetMatrix(0, 1) * other.GetMatrix(1, 0) + GetMatrix(0, 2) * other.GetMatrix(2, 0) + GetMatrix(0, 3) * other.GetMatrix(3, 0));
	result.MatrixSetup(1, 0, GetMatrix(1, 0) * other.GetMatrix(0, 0) + GetMatrix(1, 1) * other.GetMatrix(1, 0) + GetMatrix(1, 2) * other.GetMatrix(2, 0) + GetMatrix(1, 3) * other.GetMatrix(3, 0));
	result.MatrixSetup(2, 0, GetMatrix(2, 0) * other.GetMatrix(0, 0) + GetMatrix(2, 1) * other.GetMatrix(1, 0) + GetMatrix(2, 2) * other.GetMatrix(2, 0) + GetMatrix(2, 3) * other.GetMatrix(3, 0));
	result.MatrixSetup(3, 0, GetMatrix(3, 0) * other.GetMatrix(0, 0) + GetMatrix(3, 1) * other.GetMatrix(1, 0) + GetMatrix(3, 2) * other.GetMatrix(2, 0) + GetMatrix(3, 3) * other.GetMatrix(3, 0));

	result.MatrixSetup(0, 1, GetMatrix(0, 0) * other.GetMatrix(0, 1) + GetMatrix(0, 1) * other.GetMatrix(1, 1) + GetMatrix(0, 2) * other.GetMatrix(2, 1) + GetMatrix(0, 3) * other.GetMatrix(3, 1));
	result.MatrixSetup(1, 1, GetMatrix(1, 0) * other.GetMatrix(0, 1) + GetMatrix(1, 1) * other.GetMatrix(1, 1) + GetMatrix(1, 2) * other.GetMatrix(2, 1) + GetMatrix(1, 3) * other.GetMatrix(3, 1));
	result.MatrixSetup(2, 1, GetMatrix(2, 0) * other.GetMatrix(0, 1) + GetMatrix(2, 1) * other.GetMatrix(1, 1) + GetMatrix(2, 2) * other.GetMatrix(2, 1) + GetMatrix(2, 3) * other.GetMatrix(3, 1));
	result.MatrixSetup(3, 1, GetMatrix(3, 0) * other.GetMatrix(0, 1) + GetMatrix(3, 1) * other.GetMatrix(1, 1) + GetMatrix(3, 2) * other.GetMatrix(2, 1) + GetMatrix(3, 3) * other.GetMatrix(3, 1));

	result.MatrixSetup(0, 2, GetMatrix(0, 0) * other.GetMatrix(0, 2) + GetMatrix(0, 1) * other.GetMatrix(1, 2) + GetMatrix(0, 2) * other.GetMatrix(2, 2) + GetMatrix(0, 3) * other.GetMatrix(3, 2));
	result.MatrixSetup(1, 2, GetMatrix(1, 0) * other.GetMatrix(0, 2) + GetMatrix(1, 1) * other.GetMatrix(1, 2) + GetMatrix(1, 2) * other.GetMatrix(2, 2) + GetMatrix(1, 3) * other.GetMatrix(3, 2));
	result.MatrixSetup(2, 2, GetMatrix(2, 0) * other.GetMatrix(0, 2) + GetMatrix(2, 1) * other.GetMatrix(1, 2) + GetMatrix(2, 2) * other.GetMatrix(2, 2) + GetMatrix(2, 3) * other.GetMatrix(3, 2));
	result.MatrixSetup(3, 2, GetMatrix(3, 0) * other.GetMatrix(0, 2) + GetMatrix(3, 1) * other.GetMatrix(1, 2) + GetMatrix(3, 2) * other.GetMatrix(2, 2) + GetMatrix(3, 3) * other.GetMatrix(3, 2));

	result.MatrixSetup(0, 3, GetMatrix(0, 0) * other.GetMatrix(0, 3) + GetMatrix(0, 1) * other.GetMatrix(1, 3) + GetMatrix(0, 2) * other.GetMatrix(2, 3) + GetMatrix(0, 3) * other.GetMatrix(3, 3));
	result.MatrixSetup(1, 3, GetMatrix(1, 0) * other.GetMatrix(0, 3) + GetMatrix(1, 1) * other.GetMatrix(1, 3) + GetMatrix(1, 2) * other.GetMatrix(2, 3) + GetMatrix(1, 3) * other.GetMatrix(3, 3));
	result.MatrixSetup(2, 3, GetMatrix(2, 0) * other.GetMatrix(0, 3) + GetMatrix(2, 1) * other.GetMatrix(1, 3) + GetMatrix(2, 2) * other.GetMatrix(2, 3) + GetMatrix(2, 3) * other.GetMatrix(3, 3));
	result.MatrixSetup(3, 3, GetMatrix(3, 0) * other.GetMatrix(0, 3) + GetMatrix(3, 1) * other.GetMatrix(1, 3) + GetMatrix(3, 2) * other.GetMatrix(2, 3) + GetMatrix(3, 3) * other.GetMatrix(3, 3));

	return result;
}

Matrix& Matrix::operator= (const Matrix& rhs)
{
	if (this != &rhs)
	{
		SetMatrix(rhs);
	}
	return *this;

}

const Vertex Matrix::operator*(const Vertex& other) const
{
	Vertex result;

	result.SetX(GetMatrix(0, 0) * other.GetX() + GetMatrix(0, 1) * other.GetY() + GetMatrix(0, 2) * other.GetZ() + GetMatrix(0, 3) * other.GetW());
	result.SetY(GetMatrix(1, 0) * other.GetX() + GetMatrix(1, 1) * other.GetY() + GetMatrix(1, 2) * other.GetZ() + GetMatrix(1, 3) * other.GetW());
	result.SetZ(GetMatrix(2, 0) * other.GetX() + GetMatrix(2, 1) * other.GetY() + GetMatrix(2, 2) * other.GetZ() + GetMatrix(2, 3) * other.GetW());
	result.SetW(GetMatrix(3, 0) * other.GetX() + GetMatrix(3, 1) * other.GetY() + GetMatrix(3, 2) * other.GetZ() + GetMatrix(3, 3) * other.GetW());

	return result;
}

void Matrix::SetRotationX(float degrees)
{
	float radians = degrees * PI / 180.0f;
	SetIdentity();
	_m[1][1] = cos(radians); _m[1][2] = -sin(radians);
	_m[2][1] = sin(radians); _m[2][2] = cos(radians);
}

void Matrix::SetRotationY(float degrees)
{
	float radians = degrees * PI / 180.0f;
	SetIdentity();
	_m[0][0] = cos(radians); _m[0][2] = sin(radians);
	_m[2][0] = -sin(radians); _m[2][2] = cos(radians);
}

void Matrix::SetRotationZ(float degrees)
{
	float radians = degrees * PI / 180.0f;
	SetIdentity();
	_m[0][0] = cos(radians); _m[0][1] = -sin(radians);
	_m[1][0] = sin(radians); _m[1][1] = cos(radians);
}

void Matrix::SetTranslate(float tx, float ty, float tz)
{
	SetIdentity();
	_m[0][3] = tx;
	_m[1][3] = ty;
	_m[2][3] = tz;

}

void Matrix::SetScale(float sx, float sy, float sz)
{
	SetIdentity();
	_m[0][0] = sx;
	_m[0][0] = sy;
	_m[2][2] = sz;
}

void Matrix::SetViewMatrix(const Vertex& camera_position, const Vertex& view_vector, const Vertex& up_vector)
{
}


void Matrix::SetCamera(float xRotation, float yRotation, float zRotation, float xPosition, float yPosition, float zPosition)
{
	Matrix Camera, CameraPos, CameraRotX, CameraRotY, CameraRotZ;
	CameraPos.SetTranslate(-xPosition, -yPosition, -zPosition);
	CameraRotX.SetRotationX(-xRotation);
	CameraRotY.SetRotationY(-yRotation);
	CameraRotZ.SetRotationZ(-zRotation);
	Camera = CameraPos * CameraRotZ * CameraRotY * CameraRotX;
	SetMatrix(Camera);
}

void Matrix::SetOrtho(float d)
{
	SetZero();
	_m[0][0] = d;
	_m[1][1] = d;
	_m[2][2] = d;
	_m[3][3] = 1.0f;

}

void Matrix::SetPerspective(float d, float aspectRatio)
{
	SetZero();
	_m[0][0] = -d / aspectRatio;
	_m[1][1] = -d;
	_m[2][2] = -d;
	_m[3][2] = 1.0f;

}

void Matrix::SetViewvolume(float left, float right, float bottom, float top, float front, float rear)
{
	float width = right - left;
	float height = top - bottom;
	float depth = front - rear;
	SetIdentity();
	_m[0][0] = 1.0f / width;
	_m[1][1] = 1.0f / height;
	_m[2][2] = 1.0f / depth;
}

void Matrix::SetViewport(int left, int right, int top, int bottom)
{
	int width = right - left;
	int height = bottom - top;
	SetIdentity();
	_m[0][0] = width;
	_m[1][1] = -height;
	_m[2][2] = 1.0f;
	_m[0][3] = left + width / 2.0f;
	_m[1][3] = top + height / 2.0f;
	_m[2][3] = 0.0f;
}

Matrix::Matrix()
{
	SetIdentity();
}

Matrix::Matrix(const Matrix& other)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			MatrixSetup(i,j, other.GetMatrix(i,j));
}

Matrix::~Matrix()
{

}

void Matrix::SetZero()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			_m[i][j] = 0.0f;
}

void Matrix::SetIdentity()
{
	SetZero();
	_m[0][0] = _m[1][1] = _m[2][2] = _m[3][3] = 1.0f;
}

void Matrix::SetMatrix(const Matrix& other)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			_m[i][j] = other.GetMatrix(i,j);
}

float Matrix::GetMatrix(const int row, const int col) const
{
	return _m[row][col];
}

void Matrix::MatrixSetup(const int row, const int col, const float val)
{
	_m[row][col] = val;
}




