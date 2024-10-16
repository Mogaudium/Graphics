#pragma once
#include <windows.h>
#include <vector>
#include "Light.h"
#include "Vertex.h"
#include "Matrix.h"

using namespace std;

class Triangle
{
public:
	Triangle();
	Triangle(int index0, int index1, int index2);
	~Triangle();
	Triangle(const Triangle& other);//Copy tringle

	int Index(int i) const;//Get index
	Vertex Normals() const;//Get normals
	void SetNormal(Vertex & normal);//Set normals
	Vertex Centers() const;//Get center
	void SetCenter(Vertex& center);//Set center
	bool Visibility() const;//Configuration value
	void SetVisibility(bool value);//Set visibility
	COLORREF TriangleColour() const;//Get triangle colour
	void SetTriangleColour(COLORREF color);//Set triangle colour
		
	Triangle& operator= (const Triangle &rhs);//Operator

private:
	int _indices[3];
	bool _visible;
	Vertex _normal;
	Vertex _center;
	COLORREF _color;
};

class Model
{
public:
	Model();
	~Model();
	//Clear methods
	void Clear();
	void ClearVertices();
	void ClearTriangles();

	vector<Triangle>& Triangles();//Get triangles
	vector<Vertex>& Vertices();//Get vertices
	size_t Triangle_Count() const;//Get triangle count
	size_t Vertex_Count() const;//Get vertex count
	void AddVertex(float x, float y, float z);//Add vertex method
	void AddTriangle(int i0, int i1, int i2);//Add triangle method

	void CopyModel(Model& rhs);//Copy model

	void ApplyTransform(const Matrix &transform);//Transformation method
	void Dehomogenise();

	void CalculateNormals(bool CCW);//Calc normals
	void CalculateCenters();//Calc centers
	void MarkBackfaces(float eX, float eY, float eZ, bool ortho);//Back face culling method
	void ApplyDepthSorting();//Depth sorting method
	void CalcFlatShading(HDC hdc, Light light, float eX, float eY, float eZ, bool ortho);//Flat shading method

	COLORREF GetColorKa() const;//Get ambient model colour
	void SetColorKa(COLORREF color);//Set ambient model colour
	COLORREF GetColorKd() const;//Get diffuse model colour
	void SetColorKd(COLORREF color);//Set diffuse model colour
	COLORREF GetColorKs() const;//Get specular model colour
	void SetColorKs(COLORREF color);//Set specular model colour
	float GetShininess() const;//Get shininess of model
	void SetShininess(float value);//Set shineness of model

	void DrawWireFrame(HDC hdc);//Wire frame model
	void DrawSolidFill(HDC hdc);//Solid fill model
	void DrawFlatShading(HDC hdc);//Flat shading model

private:
	vector<Triangle> _triangles;
	vector<Vertex> _vertices;
	COLORREF _Ka;
	COLORREF _Kd;
	COLORREF _Ks;
	float _shininess;

};

