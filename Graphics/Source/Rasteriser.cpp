#include <windowsx.h>
#include "MD2Loader.h"
#include "Rasteriser.h"

Rasteriser app;//Rasteriser methods implementation

void Rasteriser::SceneRender(HDC hdc)// Renders the scene and sets up the parameters
{
	Model model;
	Vertex lightPos;

	float eX, eY, eZ; 
	eX = -_camera.GetMatrix(0, 3);
	eY = -_camera.GetMatrix(0, 3);
	eZ = -_camera.GetMatrix(0, 3);

	ViewportFrame(hdc);

	for (size_t i = 0; i < _models.size(); i++)
	{
		model = _models[i];

		model.ApplyTransform(_camera);

		model.CalculateCenters();

		if (_depthsort)	model.ApplyDepthSorting();

		model.CalculateCenters();
		model.CalculateNormals(true);

		lightPos = _camera * _lPos;
		_light.SetLightPosition(lightPos);

		if (_render_mode == 2) model.CalcFlatShading(hdc, _light, eX, eY, eZ, _ortho);

		model.ApplyTransform(_projection);
		model.Dehomogenise();

		model.CalculateCenters();
		model.CalculateNormals(true);

		if (_facecull)
		{
			model.MarkBackfaces(eX, eY, eZ, _ortho);
		}

		model.ApplyTransform(_viewport);

		//Switch model rendering parameters
		switch (_render_mode)
		{
		case  0: model.DrawWireFrame(hdc);
			break;
		case  1: model.DrawSolidFill(hdc);
			break;
		case  2: model.DrawFlatShading(hdc);
			break;
		default: model.DrawWireFrame(hdc);
			break;
		}

	}

	Frame(hdc);
}

void Rasteriser::Scene_Initialise(HWND _hWnd)
{
	// Load a model and add it in scene's model list
	Model MyModel;
	MD2Loader MyLoader;
	//Models params initialization
	MyLoader.Load_Model("dolphin.md2", MyModel);
	MyModel.SetColorKa(RGB(0, 0, 139));
	MyModel.SetColorKd(RGB(0, 0, 50));
	MyModel.SetColorKs(RGB(255, 255, 255));
	MyModel.SetShininess(100.0f);
	Add_Model(MyModel);

	Viewport(10, 700, 49, 662);

	// Set the camera matrix
	_camRx = 0.0f;
	_camRy = 140.0f;
	_camRz = 0.0f;
	_camZ = 600.0f;
	Matrix camera;
	camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
	Camera_Transform(camera);

	// Set the projection matrix
	_ortho = false;
	Matrix projection;
	projection.SetPerspective(200.0f, 1.0f);

	// Set the viewvolume matrix
	Matrix volume;
	volume.SetViewvolume(-400, +400, -400, +400, +400, -400);

	// Set the overall view matrix = viewvolume matrix * projection matrix
	Matrix view;
	view = volume * projection;
	Projection_Transform(view);

	_render_mode = 0;
	_depthsort = false;
	_facecull = false;
	_directional = true;
	_light.SetDirectional(_directional);
	_lPos.SetX(1500.0f);
	_lPos.SetY(1000.0f);
	_lPos.SetZ(1000.0f);
	_light.SetLightPosition(_lPos);

	_light.SetAmbient_Light(RGB(0, 0, 100));
	_light.SetDiffuse_Light(RGB(0, 0, 255));
	_light.SetSpecular_Light(RGB(0, 0, 255));
}

void Rasteriser::RenderParameters(int action)
{
	Matrix camera, projection, volume, view;

	switch (action)
	{
	case  0: if (_render_mode < 2) _render_mode = _render_mode + 1; else _render_mode = 0;
		break;
	case  1: _ortho = !_ortho;

		if (_ortho) projection.SetOrtho(0.5f);
		else projection.SetPerspective(200.0f, 1.0f);

		volume.SetViewvolume(-400, +400, -400, +400, +400, -400);
		view = volume * projection;
		Projection_Transform(view);
		break;
	case  2: _facecull = !_facecull;
		break;
	case  3: _depthsort = !_depthsort;
		break;
	case  4: _directional = !_directional;
		_light.SetDirectional(_directional);
		break;
	case 10:	 
		_camRx = 0.0f;
		_camRy = 140.0f;
		_camRz = 0.0f;
		_camZ = 600.0f;
		camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
		Camera_Transform(camera);
		break;
	case 11:	 _camRx = (int)(_camRx + 10.0f) % 360;
		camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
		Camera_Transform(camera);
		break;
	case 12:	_camRx = (int)(_camRx - 10.0f) % 360;
		camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
		Camera_Transform(camera);
		break;
	case 13:	_camRy = (int)(_camRy - 10.0f) % 360;
		camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
		Camera_Transform(camera);
		break;
	case 14:	_camRy = (int)(_camRy + 10.0f) % 360;
		camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
		Camera_Transform(camera);
		break;

	case 17:	_camZ = _camZ - 10.0f;
		camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
		Camera_Transform(camera);
		break;
	case 18:	_camZ = _camZ + 10.0f;
		camera.SetCamera(_camRx, _camRy, _camRz, 0, 0, _camZ);
		Camera_Transform(camera);
		break;
	}
}

void Rasteriser::Viewport(int left, int right, int top, int bottom)
{
	_viewportrect.left = left;
	_viewportrect.top = top;
	_viewportrect.right = right;
	_viewportrect.bottom = bottom;
	_viewport.SetViewport(left, right, top, bottom);
}

void Rasteriser::ViewportFrame(HDC hdc)//Creates the frame of the viewport
{
	POINT points[4];
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(124, 252, 0));// Pen for the green border of viewport
	HGDIOBJ oldPen = SelectPen(hdc, pen);

	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));//Brush to fill the viewport with the black colour
	HBRUSH oldBrush = SelectBrush(hdc, brush);

	//Position of the viewport
	points[0].x = (int)_viewportrect.left;      points[0].y = (int)_viewportrect.top;
	points[1].x = (int)_viewportrect.right - 1; points[1].y = (int)_viewportrect.top;
	points[2].x = (int)_viewportrect.right - 1; points[2].y = (int)_viewportrect.bottom - 1;
	points[3].x = (int)_viewportrect.left;      points[3].y = (int)_viewportrect.bottom - 1;

	Polygon(hdc, points, 4);

	SelectBrush(hdc, oldBrush);
	DeleteObject(brush);

	SelectPen(hdc, oldPen);
	DeleteObject(pen);
}

void Rasteriser::Frame(HDC hdc)//Creates the frames for the text
{
	POINT points1[4];//Config tex frame
	POINT points2[4];//Instructions text frame
	wchar_t outstr[256];

	HPEN pen = CreatePen(PS_SOLID, 4, RGB(124, 252, 0));//Pen for the green border of text frame
	HGDIOBJ oldPen = SelectPen(hdc, pen);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));//Brush for the white background of text frame
	HBRUSH oldBrush = SelectBrush(hdc, brush);

	//Positon of first text frame
	points1[0].x = 700; points1[0].y = 50;
	points1[1].x = 880; points1[1].y = 50;
	points1[2].x = 880; points1[2].y = 180;
	points1[3].x = 700; points1[3].y = 180;

	Polygon(hdc, points1, 4);

	SelectBrush(hdc, oldBrush);
	DeleteObject(brush);

	SelectPen(hdc, oldPen);
	DeleteObject(pen);


	//Switch the text on screen depending on actions
	switch (_render_mode)
	{
	case  0: String_Output(hdc, 710, 55, 18, RGB(0, 0, 0), L"Draw: Wireframe");
		break;
	case  1: String_Output(hdc, 710, 55, 18, RGB(0, 0, 0), L"Draw: Solid-Fill");
		break;
	case  2: String_Output(hdc, 710, 55, 18, RGB(0, 0, 0), L"Draw: Flat-Shading");
		break;
	default: String_Output(hdc, 710, 55, 18, RGB(0, 0, 0), L"Draw: Wireframe");
		break;
	}

	if (_depthsort)	String_Output(hdc, 710, 75, 18, RGB(0, 0, 0), L"Depth Sorting: ON");
	else String_Output(hdc, 710, 75, 18, RGB(0, 0, 0), L"Depth Sorting: OFF");

	if (_facecull)	String_Output(hdc, 710, 95, 18, RGB(0, 0, 0), L"Back-face Culling: ON");
	else String_Output(hdc, 710, 95, 18, RGB(0, 0, 0), L"Back-face Culling: OFF");

	if (_ortho)	String_Output(hdc, 710, 115, 18, RGB(0, 0, 0), L"Projection: Ortho");
	else String_Output(hdc, 710, 115, 18, RGB(0, 0, 0), L"Projection: Perspective");

	if (_directional)	String_Output(hdc, 710, 135, 18, RGB(0, 0, 0), L"Light: Directional");
	else String_Output(hdc, 710, 135, 18, RGB(0, 0, 0), L"Light: Point-light");

	swprintf(outstr, 256, L"Camera: RotX=%.2f; RotY=%.2f; RotZ=%.2f; PosZ=%.2f;\0", _camRx, _camRy, _camRz, _camZ);
	String_Output(hdc, 160, 100, 18, RGB(0, 0, 0), (LPCTSTR)outstr);

	swprintf(outstr, 256, L"Light Position: PosX=%.2f; PosY=%.2f; PosZ=%.2f;\0", _light.LightPosition().GetX(), _light.LightPosition().GetY(), _light.LightPosition().GetZ());
	String_Output(hdc, 160, 120, 18, RGB(0, 0, 0), (LPCTSTR)outstr);

	//Position of second text frame
	points2[0].x = 700; points2[0].y = 495;
	points2[1].x = 1020; points2[1].y = 495;
	points2[2].x = 1020; points2[2].y = 660;
	points2[3].x = 700; points2[3].y = 660;

	Polygon(hdc, points2, 4);

	//Instructions list
	String_Output(hdc, 710, 500, 18, RGB(0, 0, 0), L"Instructions: Press 'TAB' to switch render mode");
	String_Output(hdc, 710, 520, 18, RGB(0, 0, 0), L"Press 'LMB' to turn on back face culling");
	String_Output(hdc, 710, 540, 18, RGB(0, 0, 0), L"Press 'RMB' to turn on depth sorting");
	String_Output(hdc, 710, 560, 18, RGB(0, 0, 0), L"Press 'O' to change projection style");
	String_Output(hdc, 710, 580, 18, RGB(0, 0, 0), L"Press 'L' to change ligh source");
	String_Output(hdc, 710, 600, 18, RGB(0, 0, 0), L"Press '+' or '-' to change the zoom");
	String_Output(hdc, 710, 620, 18, RGB(0, 0, 0), L"Press arrows to move the model");
	String_Output(hdc, 710, 640, 18, RGB(0, 0, 0), L"Press 'D' to reset settings");
}



void Rasteriser::String_Output(HDC hdc, int xPos, int yPos, int fSize, COLORREF textColor, LPCTSTR text)//Outputs the text on screen
{
	HFONT hFont, hOldFont;

	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		TextOut(hdc, xPos, yPos, text, lstrlen(text));
	}
	DeleteObject(hFont);
}

void Rasteriser::Add_Model(Model& model)//Add model to the scene
{
	_models.push_back(model);
}

void Rasteriser::Model_Transform(int modeltransform, Matrix transform)//Transform the model 
{
	if (modeltransform > _models.size() - 1)
		return;

	_models[modeltransform].ApplyTransform(transform);
}

void Rasteriser::View_Transform(Matrix view)//Set view
{
	_view.SetMatrix(view);
}

void Rasteriser::Camera_Transform(Matrix cam)//Set camera
{
	_camera.SetMatrix(cam);
}

void Rasteriser::Projection_Transform(Matrix projection)//Set projection
{
	_projection.SetMatrix(projection);
}





