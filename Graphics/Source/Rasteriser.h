#pragma once
#include "Framework.h"
#include "Light.h"
#include "Model.h"
#include "Matrix.h"

//Rasterise functions initialising

using namespace std;

class Rasteriser : public Framework
{
public:
	void Add_Model(Model& model);//Add model function
	void Model_Transform(int modeltransform, Matrix transform);//Model transform function
	void View_Transform(Matrix view);//View transform function
	void Camera_Transform(Matrix cam);//Camera transform function
	void Projection_Transform(Matrix projection);//Projection transform function
	void Viewport(int left, int right, int top, int bottom);//Viewport function

	virtual void Scene_Initialise(HWND _hWnd);//Virtual function to initialise scene
	virtual void SceneRender(HDC hdc);//Virtual function to render the scene
	virtual void RenderParameters(int action);//Render parameters for the scene

	void String_Output(HDC hdc, int xPos, int yPos, int fSize, COLORREF textColor, LPCTSTR text);//Function to output string on the sceen
	void Frame(HDC hdc);//Function to create/draw frame for text on screen
	void ViewportFrame(HDC hdc); //Function to create/draw frame for viewport on screen

private:
	vector<Model> _models; //Model loaded in the original scene
	vector<Model> _models_transformed; //Transformed model in the scene 
	RECT	 _viewportrect; //Rectangle of the viewport
	Matrix	 _viewport; //Matrix of viewport
	Matrix	 _view; //View matrix
	Matrix	 _camera; //Matrtix of camera
	Matrix	 _projection; //Matrix of projection
	int      _render_mode;//Depending on render mode the scene changes
	bool     _depthsort;//Configuration value for depthsort setting 
	bool     _facecull;//Configuration value for facefull setting 
	bool     _ortho;//Configuration value for ortho setting 
	float    _camRx, _camRy, _camRz, _camZ;
	bool     _directional;//Configuration value for light setting 
	Light    _light;//Light value
	Vertex   _lPos;//Configuration value for light position

};

