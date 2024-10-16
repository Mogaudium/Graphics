#pragma once
#include <windows.h>
#include <vector>
#include "Vertex.h"

using namespace std;

//Light functions

class Light
{
public:
	Light();
	~Light();
	Light(const Light& other);
	Vertex LightPosition() const;//Get light position
	void SetLightPosition(Vertex& pos);//Set light position
	bool Directional_Light() const;//Configuration value for directional light
	void SetDirectional(bool value);//Set directional light
	COLORREF Ambient_Light() const;//Get ambient light colour
	void SetAmbient_Light(COLORREF color);//Set ambient light colour
	COLORREF Diffuse_Light() const;//Get diffuse light colour
	void SetDiffuse_Light(COLORREF color);//Set diffuse light colour
	COLORREF Specular_Light() const;//Get specular light colour
	void SetSpecular_Light(COLORREF color);//Set specular light colour
		
	Light& operator = (const Light &rhs);//Assign operator

private:
	COLORREF AmbLight;//Ambient light
	COLORREF DiffuseLight;//Diffuse light
	COLORREF SpecularLight;//Specular light
	Vertex LightPos;//Light position
	bool _directional;//Configuration file
};


