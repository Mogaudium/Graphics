#include "Framework.h"

Framework *	_thisFramework = NULL;

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

//Entry point
int APIENTRY wWinMain(_In_	   HINSTANCE hInstance,
				  	  _In_opt_ HINSTANCE hPrevInstance,
					  _In_	   LPWSTR    lpCmdLine,
					  _In_	   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	if (_thisFramework)
	{
		return _thisFramework->Run(hInstance, nCmdShow);
	}
	return -1;
}


Framework::Framework()
{
	_thisFramework = this;
}

Framework::~Framework()
{
}

int Framework::Run(HINSTANCE hInstance, int nCmdShow)
{
	_hInstance = hInstance;
	if (!InitialiseMainWindow(nCmdShow))
	{
		return -1;
	}
	return MainLoop();
}

int Framework::MainLoop()
{
	MSG msg;

	HACCEL hAccelTable = LoadAccelerators(_hInstance, MAKEINTRESOURCE(IDC_RASTERISER));

	//Message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

bool Framework::InitialiseMainWindow(int nCmdShow)
{
	#define MAX_LOADSTRING 100

	WCHAR windowTitle[MAX_LOADSTRING];          
	WCHAR windowClass[MAX_LOADSTRING];            
	
	LoadStringW(_hInstance, IDS_APP_TITLE, windowTitle, MAX_LOADSTRING);
	LoadStringW(_hInstance, IDC_RASTERISER, windowClass, MAX_LOADSTRING);

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_RASTERISER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = windowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (!RegisterClassExW(&wcex))
	{
		return false;
	}

	_hWnd = CreateWindowW(windowClass, 
						  windowTitle, 
					      WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
					      nullptr, nullptr, _hInstance, nullptr);
	if (!_hWnd)
	{
		return false;
	}

	Scene_Initialise(_hWnd);//Scene initialization


	ShowWindow(_hWnd, nCmdShow);
	UpdateWindow(_hWnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_thisFramework != NULL)
	{
		return _thisFramework->MsgProc(hWnd, message, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

LRESULT Framework::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			
			SceneRender(hdc);//Rendering parameters 

			EndPaint(hWnd, &ps);
		}
		break;

		//Mouse input
		case WM_LBUTTONDOWN: //By pressing left mouse button, back face culling is turning on
			RenderParameters(2);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case WM_RBUTTONDOWN://By pressing right mouse button, depth sorting is turning on
			RenderParameters(3);
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case WM_LBUTTONUP:
			//OnLButtonUp(hWnd, lParam);
			break;

		case WM_MOUSEMOVE:
			//OnMouseMove(hWnd, lParam);
			break;	


		case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_TAB://By pressing tab buttom, the draw function changes
				RenderParameters(0);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case 'O':
			case 'o':
				RenderParameters(1);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case'l'://By pressing 'l'buttom, the light function changes
			case'L':
				RenderParameters(4);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case VK_RIGHT://By pressing right arrow the Y axis changes by 10
				RenderParameters(13);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case VK_LEFT://By pressing right arrow the Y axis changes by 10
				RenderParameters(14);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case VK_UP://By pressing up button, X axis changes by 10
				RenderParameters(12);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case VK_DOWN://By pressing up button, X axis changes by 10
				RenderParameters(11);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case 'd':// Sets camera to default possition
			case 'D':
				RenderParameters(10);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case VK_OEM_PLUS://By pressing + button the model zooms in
				RenderParameters(17);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case VK_OEM_MINUS://By pressing - button, the model zooms out
				RenderParameters(18);
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			default:
				break;
			}
		}
		break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Framework::Scene_Initialise(HWND _hWnd)
{

}

void Framework::SceneRender(HDC hdc)
{
}

void Framework::RenderParameters(int action)
{
}



