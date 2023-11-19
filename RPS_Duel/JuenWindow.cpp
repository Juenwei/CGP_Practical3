#include "JuenWindow.h"
#include<iostream>
#include<stdlib.h>

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	JuenWindow *myWindow = myWindow->GetWindowInstance();
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYUP:
	
		break;
	case WM_KEYDOWN:
		if (wParam == 27)
		{
			myWindow->quitProgram();
		}
		break;
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Static initialization

JuenWindow *JuenWindow::instance = NULL;

JuenWindow::JuenWindow()
{
	
	hInstance = GetModuleHandle(NULL);
	g_hWnd = NULL;
}

JuenWindow::~JuenWindow()
{
}


JuenWindow *JuenWindow::GetWindowInstance()
{
	if (!instance)
	{
		instance = new JuenWindow;

	}
	return instance;
}

void JuenWindow ::ReleaseWindowInstance()
{
	if (instance!=NULL)
	{
		delete instance;
		instance = NULL;
	}
	
}

void JuenWindow::quitProgram()
{
	PostQuitMessage(0);
}


void JuenWindow:: InitializeWindow()
{
	//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_JPG1));
	//wndClass.hCursor = LoadCursorFromFile("aero_link_l.cur");
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "JuenWei's Window", WS_OVERLAPPEDWINDOW, 0, 100, WINSCREEN_WIDTH, WINSCREEN_HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);
}

bool JuenWindow::WindowIsRunning()
{
	ZeroMemory(&msg, sizeof(msg));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//Check event 
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) break;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);//Send the key value
	}

	return msg.message != WM_QUIT;
}


void JuenWindow::CleanUpWindow()
{
	UnregisterClass(wndClass.lpszClassName, hInstance);
}