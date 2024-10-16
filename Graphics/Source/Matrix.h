#pragma once

#include "Vertex.h"

//Matrix functions

class Matrix
{
public:

	Matrix();
	Matrix(const Matrix& other);//Constuctor
	~Matrix();//Destructor
	float GetMatrix(const int row, const int col) const;//Get matrix value 
	void MatrixSetup(const int row, const int col, const float val);//Set matrix value
	Matrix& operator= (const Matrix &rhs);//Matrix operator
	const Matrix operator*(const Matrix &other) const;//Matrix multiplication
	const Vertex operator*(const Vertex &other) const;//Matrix multiplication

	//Set functions

	void				SetZero();//Set values for matrixes
	void				SetIdentity();//Set values for matrixes
	void				SetMatrix(const Matrix& other);//Copy matrices
	void				SetRotationX(float degrees);//Set X axis
	void				SetRotationY(float degrees);//Set Y axis
	void				SetRotationZ(float degrees);//Set Z axis
	void				SetTranslate(float tx, float ty, float tz);
	void				SetScale(float sx, float sy, float sz);//Set scale
	void				SetViewMatrix(const Vertex& camera_position, const Vertex& view_vector, const Vertex& up_vector);//Set view matrix
	void				SetCamera(float xRotation, float yRotation, float zRotation, float xPosition, float yPosition, float zPosition);//Set camera
	void				SetOrtho(float d);//Set ortho
	void				SetPerspective(float d, float aspectRatio);//Set perspective
	void                SetViewvolume(float left, float right, float bottom, float top, float front, float rear);//Set viewvolume
	void				SetViewport(int left, int right, int top, int bottom);//Set viewport
	
private:
	float				_m[4][4];
};
