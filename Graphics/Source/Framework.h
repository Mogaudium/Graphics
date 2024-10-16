#pragma once
#include <windows.h>
#include "resource.h"
#include "Model.h"
#include "Matrix.h"

//Framework functions

class Framework
{
public:
	Framework();
	virtual ~Framework();

	int Run(HINSTANCE hInstance, int nCmdShow);

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void Scene_Initialise(HWND _hWnd);
	virtual void SceneRender(HDC hdc);

	virtual void RenderParameters(int action);


private:
	HINSTANCE	_hInstance;
	HWND		_hWnd;

	bool InitialiseMainWindow(int nCmdShow);
	int MainLoop();

};