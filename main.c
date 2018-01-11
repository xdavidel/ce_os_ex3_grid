#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  

// Global variables  

// The main window class name.  
static TCHAR szWindowClass[] = _T("Active Grid");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("WinAPI - Active Grid");

HINSTANCE hInst;

HWND txtWidth;
HWND txtHeight;
int step = 20;
BOOL drawGrid = FALSE;
size_t width = 0;
size_t height = 0;


// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void registerDialogClass(HINSTANCE hInst);
void displayDialog(HWND hWnd);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{

	registerDialogClass(hInstance);
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if(!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
				   _T("Call to RegisterClassEx failed!"),
				   szTitle,
				   NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

					   // The parameters to CreateWindow explained:  
					   // szWindowClass: the name of the application  
					   // szTitle: the text that appears in the title bar  
					   // WS_OVERLAPPEDWINDOW: the type of window to create  
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
					   // 500, 100: initial size (width, length)  
					   // NULL: the parent of this window  
					   // NULL: this application does not have a menu bar  
					   // hInstance: the first parameter from WinMain  
					   // NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if(!hWnd)
	{
		MessageBox(NULL,
				   _T("Call to CreateWindow failed!"),
				   szTitle,
				   NULL);

		return 1;
	}



	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
//  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("0");

	TCHAR widthBuffer[200];
	TCHAR heightBuffer[200];

	int res;

	switch(message)
	{
		case WM_CREATE:
			displayDialog(hWnd);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			txtWidth = CreateWindow("Edit", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 5, 5, 100, 20, hWnd, NULL, NULL, NULL);
			txtHeight = CreateWindow("Edit", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 5, 30, 100, 20, hWnd, NULL, NULL, NULL);
			CreateWindow("Button", "Generate", WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 5, 100, 45, hWnd, (HMENU)1, NULL, NULL);

			if(drawGrid)
			{
				for(size_t i = 0; i < height; i++)
				{
					for(size_t j = 0; j < width; j++)
					{
						CreateWindow("Edit", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 5 + j * step, 60 + i *step, 10, 10, hWnd, NULL, NULL, NULL);
						//TextOut(hdc, j * step, i * step + 50, greeting, _tcslen(greeting));
					}
				}

			}

			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case 1:
					GetWindowText(txtWidth, widthBuffer, 20);
					GetWindowText(txtHeight, heightBuffer, 20);
					
					width = atoi(widthBuffer);
					height = atoi(heightBuffer);
					drawGrid = TRUE;
					
					//RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
					res = AnimateWindow(hWnd, 200, AW_HIDE);

					break;
				default:
					break;
			}

			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}

	return 0;
}

LRESULT CALLBACK  DialogProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		default:
			break;
	}
}

void registerDialogClass(HINSTANCE hInst)
{
	WNDCLASS dialog = {0};
	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_CROSS);
	dialog.hInstance = hInst;
	dialog.lpszClassName = _T("ChooseGridDialog");
	dialog.lpfnWndProc = DialogProcedure;

	RegisterClass(&dialog);
}

void displayDialog(HWND hWnd)
{
	CreateWindow(_T("ChooseGridDialog"), _T("Select Width and Height"), WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 200, 200, hWnd, NULL, NULL, NULL);
}