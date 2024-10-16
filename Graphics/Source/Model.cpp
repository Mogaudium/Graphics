#include <windowsx.h>
#include <math.h>
#include <algorithm>  
#include "Model.h"

//Model methods implementation

Triangle::Triangle()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_visible = true;
	_normal.SetX(0.0f);
	_normal.SetY(0.0f);
	_normal.SetZ(0.0f);
	_normal.SetW(1.0f);
	_center.SetX(0.0f);
	_center.SetY(0.0f);
	_center.SetZ(0.0f);
	_center.SetW(1.0f);
	_color = RGB(128, 128, 128);
}

Triangle::Triangle(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_visible = true;
	_normal.SetX(0.0f);
	_normal.SetY(0.0f);
	_normal.SetZ(0.0f);
	_normal.SetW(1.0f);
	_center.SetX(0.0f);
	_center.SetY(0.0f);
	_center.SetZ(0.0f);
	_center.SetW(1.0f);
	_color = RGB(128, 128, 128);
}

// Copy constructor implementation
Triangle::Triangle(const Triangle& other)
{
	_indices[0] = other.Index(0);
	_indices[1] = other.Index(1);
	_indices[2] = other.Index(2);
	_visible = other.Visibility();
	_normal = other.Normals();
	_center = other.Centers();
	_color = other.TriangleColour();
}

// Destructor does not need to do anything

Triangle::~Triangle()
{
}


int Triangle::Index(int i) const
{
	return _indices[i];
}

bool Triangle::Visibility() const
{
	return _visible;
}

void Triangle::SetVisibility(bool value)
{
	_visible = value;
}


Vertex Triangle::Normals() const
{
	return _normal;
}

void Triangle::SetNormal(Vertex & normal)
{
	_normal = normal;
}

Vertex Triangle::Centers() const
{
	return _center;
}

void Triangle::SetCenter(Vertex& center)
{
	_center = center;
}

COLORREF Triangle::TriangleColour() const
{
	return _color;
}

void Triangle::SetTriangleColour(COLORREF color)
{
	_color = color;
}



Triangle& Triangle::operator=(const Triangle& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_indices[0] = rhs.Index(0);
		_indices[1] = rhs.Index(1);
		_indices[2] = rhs.Index(2);
		_visible = rhs.Visibility();
		_normal = rhs.Normals();
		_center = rhs.Centers();
	}
	return *this;
}

Model::Model()
{
	_Ka = RGB(0, 192, 192);
	_Kd = RGB(0, 192, 192);
	_Ks = RGB(0, 192, 192);
	_shininess = 30.0f;
}

Model::~Model()
{
}

void Model::Clear()
{
	ClearTriangles();
	ClearVertices();
}

void Model::ClearVertices()
{
	_vertices.clear();
}

void Model::ClearTriangles()
{
	_triangles.clear();
}

vector<Triangle>& Model::Triangles()
{
	return _triangles;
}

vector<Vertex>& Model::Vertices()
{
	return _vertices;
}

size_t Model::Triangle_Count() const
{
	return _triangles.size();
}

size_t Model::Vertex_Count() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex v;
	v = Vertex(x,y,z);
	_vertices.push_back (v);
}

void Model::AddTriangle(int i0, int i1, int i2)
{
	Triangle t;
	t = Triangle(i0, i1, i2);
	_triangles.push_back (t);
}

COLORREF Model::GetColorKa() const
{
	return _Ka;
}

void Model::SetColorKa(COLORREF color)
{
	_Ka = color;
}

COLORREF Model::GetColorKd() const
{
	return _Kd;
}

void Model::SetColorKd(COLORREF color)
{
	_Kd = color;
}

COLORREF Model::GetColorKs() const
{
	return _Ks;
}

void Model::SetColorKs(COLORREF color)
{
	_Ks = color;
}

float Model::GetShininess() const
{
	return _shininess;
}
void Model::SetShininess(float value)
{
	_shininess = value;
}


void Model::CopyModel(Model& rhs)
{
	vector<Triangle> triangles;
	vector<Vertex> vertices;
	
	
	triangles = rhs.Triangles();
	vertices = rhs.Vertices();
	for ( int i = 0; i < rhs.Triangle_Count(); ++i )
	{
		// Call model member function to add a new polygon to the list of triangles
		AddTriangle(triangles[i].Index(0), triangles[i].Index(1), triangles[i].Index(2));
	}

	// Vertex array initialization
	for( int i = 0; i < rhs.Vertex_Count(); ++i )
	{
		// Call model member function to add a new vertex to the list of vertices		
		AddVertex(vertices[i].GetX(),vertices[i].GetY(),vertices[i].GetZ());
	}

	_Ka = rhs.GetColorKa();
	_Kd = rhs.GetColorKd();
	_Ks = rhs.GetColorKs();
	_shininess = rhs.GetShininess();
	
}



void Model::ApplyTransform(const Matrix &transform)
{
	Vertex vC;
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_vertices[i] = transform * _vertices[i];
	}
	for (size_t i = 0; i < _triangles.size(); i++)
	{
		vC = transform * _triangles[i].Centers();
		_triangles[i].SetCenter(vC);
	}
}

void Model::Dehomogenise()
{
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_vertices[i].Dehomogenise();
	}
}

// Calculates Face Normals of Model
void Model::CalculateNormals(bool CCW)
{
	Vertex v0, v1, v2, vA, vB, vN;
	
	for (size_t i = 0; i < _triangles.size(); i++)
	{
		v0 = _vertices[_triangles[i].Index(0)];
		v1 = _vertices[_triangles[i].Index(1)];
		v2 = _vertices[_triangles[i].Index(2)];

		vA = v1 - v0;
		vB = v2 - v0;
				
		if (CCW)
			vN = vA.CrossProduct(vB);
		else
			vN = vB.CrossProduct(vA);

		vN.Normalise();
		_triangles[i].SetNormal(vN);
	}
}

// Calculates Face Center of Model
void Model::CalculateCenters()
{
	Vertex v0, v1, v2, vC;

	for (size_t i = 0; i < _triangles.size(); i++)
	{
		v0 = _vertices[_triangles[i].Index(0)];
		v1 = _vertices[_triangles[i].Index(1)];
		v2 = _vertices[_triangles[i].Index(2)];

		vC.SetX((v0.GetX() + v1.GetX() + v2.GetX()) / 3.0f);
		vC.SetY((v0.GetY() + v1.GetY() + v2.GetY()) / 3.0f);
		vC.SetZ((v0.GetZ() + v1.GetZ() + v2.GetZ()) / 3.0f);
		vC.SetW(1.0f);

		_triangles[i].SetCenter(vC);
	}
}

// Marks Backfaces of Model
void Model::MarkBackfaces(float eX, float eY, float eZ, bool ortho)
{	
	float result;
	Vertex v0, v1, v2, vN, vC, vE; //Vertex, normal, center and eye vectors

	for (size_t i = 0; i < _triangles.size(); i++){

		vN = _triangles[i].Normals();
		vC = _triangles[i].Centers();
		
		if (ortho) vE = Vertex(eX, eY, eZ);
		else vE = Vertex(eX, eY, eZ) - vC;

		result = vN.DotProduct(vE);
		
		if (result <= 0)
			_triangles[i].SetVisibility(false);
		else
			_triangles[i].SetVisibility(true);

	}
}

// Apply Depth Sorting on Model Triangles
void Model::ApplyDepthSorting()
{
	
	std::sort(_triangles.begin(), _triangles.end(), [](const Triangle& lhs, const Triangle& rhs) {return lhs.Centers().GetZ() < rhs.Centers().GetZ(); });
	
}


void Model::DrawWireFrame(HDC hdc)
{
	int v0_inx, v1_inx, v2_inx;

	if (_triangles.size() == 0)
	{
		return;
	}
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//Black pen creation
	HGDIOBJ oldPen = SelectObject(hdc, pen);

	for (size_t i = 0; i < _triangles.size(); i++)
	{
		if (_triangles[i].Visibility()==true)
		{
			v0_inx = _triangles[i].Index(0);
			v1_inx = _triangles[i].Index(1);
			v2_inx = _triangles[i].Index(2);
		
			MoveToEx(hdc, (int)_vertices[v0_inx].GetX(), (int)_vertices[v0_inx].GetY(), NULL);
		
			LineTo(hdc, (int)_vertices[v1_inx].GetX(), (int)_vertices[v1_inx].GetY());
			LineTo(hdc, (int)_vertices[v2_inx].GetX(), (int)_vertices[v2_inx].GetY());
			LineTo(hdc, (int)_vertices[v0_inx].GetX(), (int)_vertices[v0_inx].GetY());
		}

	}
	SelectObject(hdc, oldPen);
	DeleteObject(pen);

}

void Model::DrawSolidFill(HDC hdc)
{
	int v0_inx, v1_inx, v2_inx;
	POINT points[3];
	POINT point;

	if (_triangles.size() == 0)
	{
		return;
	}
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//Black pen creation
	HGDIOBJ oldPen = SelectPen(hdc, pen);

	HBRUSH brush = CreateSolidBrush(RGB(240, 240, 240));// Whitish colour brush creation
	HBRUSH oldBrush = SelectBrush(hdc, brush);

	for (size_t i = 0; i < _triangles.size(); i++)
	{
		if (_triangles[i].Visibility() == true)
		{
			v0_inx = _triangles[i].Index(0);
			v1_inx = _triangles[i].Index(1);
			v2_inx = _triangles[i].Index(2);

			point.x = (int)_vertices[v0_inx].GetX(); point.y = (int)_vertices[v0_inx].GetY();
			points[0] = point;
			point.x = (int)_vertices[v1_inx].GetX(); point.y = (int)_vertices[v1_inx].GetY();
			points[1] = point;
			point.x = (int)_vertices[v2_inx].GetX(); point.y = (int)_vertices[v2_inx].GetY();
			points[2] = point;

			Polygon(hdc, points, 3);

			MoveToEx(hdc, point.x, point.y, NULL);

			LineTo(hdc, point.x+1, point.y);
			LineTo(hdc, point.x+1, point.y+1);
			LineTo(hdc, point.x, point.y+1);
			LineTo(hdc, point.x, point.y);
			
		}

	}
	SelectBrush(hdc, oldBrush);
	DeleteObject(brush);

	SelectPen(hdc, oldPen);
	DeleteObject(pen);

}

void Model::CalcFlatShading(HDC hdc, Light light, float eX, float eY, float eZ, bool ortho)
{
	COLORREF faceColor;
	Vertex vN, vC, vL, vE, vH;
	float cD, cS;
	float totR, totG, totB;

	if (_triangles.size() == 0)
	{
		return;
	}

	for (size_t i = 0; i < _triangles.size(); i++)
	{
			vN = _triangles[i].Normals();
			vN.Normalise();
			vC = _triangles[i].Centers();
			
			if (light.Directional_Light()) vL = light.LightPosition();
			else vL = light.LightPosition() - vC;
			vL.Normalise();

			cD = vN.DotProduct(vL);

			if (ortho) vE = Vertex(eX, eY, eZ);
			else vE = Vertex(eX, eY, eZ) - vC;
			vE.Normalise();

			vH = vL + vE;
			vH.Normalise();

			cS = pow(vN.DotProduct(vH), GetShininess());

			if (cD <= 0) { cD = 0; cS = 0; }

			totR = (GetRValue(GetColorKa()) * GetRValue(light.Ambient_Light()) / 255.0f +
					cD * GetRValue(GetColorKd()) * GetRValue(light.Diffuse_Light()) / 255.0f +
					cS * GetRValue(GetColorKs()) * GetRValue(light.Specular_Light()) / 255.0f);
			totG = (GetGValue(GetColorKa()) * GetGValue(light.Ambient_Light()) / 255.0f +
					cD * GetGValue(GetColorKd()) * GetGValue(light.Diffuse_Light()) / 255.0f +
					cS * GetGValue(GetColorKs()) * GetGValue(light.Specular_Light()) / 255.0f);
			totB = (GetBValue(GetColorKa()) * GetBValue(light.Ambient_Light()) / 255.0f +
					cD * GetBValue(GetColorKd()) * GetBValue(light.Diffuse_Light()) / 255.0f +
					cS * GetBValue(GetColorKs()) * GetBValue(light.Specular_Light()) / 255.0f);

			if (totR > 255.0f) totR = 255.0f;
			if (totG > 255.0f) totG = 255.0f;
			if (totB > 255.0f) totB = 255.0f;

			faceColor = RGB((int)totR, (int)totG, (int)totB);
			
			_triangles[i].SetTriangleColour(faceColor);

	}
	
}

void Model::DrawFlatShading(HDC hdc)
{
	int v0_inx, v1_inx, v2_inx;
	POINT points[3];
	POINT point;
	COLORREF faceColor;
	
	if (_triangles.size() == 0)
	{
		return;
	}

	for (size_t i = 0; i < _triangles.size(); i++)
	{
		if (_triangles[i].Visibility() == true)
		{
			v0_inx = _triangles[i].Index(0);
			v1_inx = _triangles[i].Index(1);
			v2_inx = _triangles[i].Index(2);

			point.x = (int)_vertices[v0_inx].GetX(); point.y = (int)_vertices[v0_inx].GetY();
			points[0] = point;
			point.x = (int)_vertices[v1_inx].GetX(); point.y = (int)_vertices[v1_inx].GetY();
			points[1] = point;
			point.x = (int)_vertices[v2_inx].GetX(); point.y = (int)_vertices[v2_inx].GetY();
			points[2] = point;

			faceColor = _triangles[i].TriangleColour();

			HPEN pen = CreatePen(PS_SOLID, 1, faceColor);
			HGDIOBJ oldPen = SelectPen(hdc, pen);

			HBRUSH brush = CreateSolidBrush(faceColor);
			HBRUSH oldBrush = SelectBrush(hdc, brush);

			Polygon(hdc, points, 3);

			SelectBrush(hdc, oldBrush);
			DeleteObject(brush);

			SelectPen(hdc, oldPen);
			DeleteObject(pen);

		}

	}

}



