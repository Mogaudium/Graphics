#include <windowsx.h>
#include <algorithm>  
#include "Light.h"

//Light functions

bool Light::Directional_Light() const//Get directional light
{
	return _directional;
}

void Light::SetDirectional(bool value)//Set directional light value
{
	_directional = value;
}

Vertex Light::LightPosition() const//Get light position
{
	return LightPos;
}

void Light::SetLightPosition(Vertex& pos)//Set light position
{
	LightPos = pos;
}

COLORREF Light::Ambient_Light() const//Get ambient light
{
	return AmbLight;
}

void Light::SetAmbient_Light(COLORREF color)//Set ambient light
{
	AmbLight = color;
}

COLORREF Light::Diffuse_Light() const//Get diffuse light 
{
	return DiffuseLight;
}

void Light::SetDiffuse_Light(COLORREF color)//Set diffuse light
{
	DiffuseLight = color;
}

COLORREF Light::Specular_Light() const//Get specular light 
{
	return SpecularLight;
}

void Light::SetSpecular_Light(COLORREF color)//Set specular light
{
	SpecularLight = color;
}

Light::Light()
{
	_directional = true;
	LightPos.SetX(0.0f);
	LightPos.SetY(0.0f);
	LightPos.SetZ(1.0f);
	LightPos.SetW(1.0f);
	AmbLight = RGB(32, 32, 32);
	DiffuseLight = RGB(128, 128, 128);
	SpecularLight = RGB(0, 0, 255);
}

Light::Light(const Light& other)//Copy light
{
	_directional = other.Directional_Light();
	LightPos = other.LightPosition();
	AmbLight = other.Ambient_Light();
	DiffuseLight = other.Diffuse_Light();
	SpecularLight = other.Specular_Light();
}

Light::~Light()//Destructor
{
}





