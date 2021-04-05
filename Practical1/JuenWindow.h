#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include"resource.h"
#define WINSCREEN_WIDTH 1080
#define WINSCREEN_HEIGHT 720
class JuenWindow
{

private:
	static JuenWindow *instance;
	HINSTANCE hInstance;
	WNDCLASS wndClass;
	

public:
	HWND g_hWnd;
	MSG msg;
	JuenWindow();
	~JuenWindow();
	
	void InitializeWindow();

	bool WindowIsRunning();

	void CleanUpWindow();

	static JuenWindow* GetWindowInstance();
	static void ReleaseWindowInstance();


	//void ChangeCursor();

	void quitProgram();
};

