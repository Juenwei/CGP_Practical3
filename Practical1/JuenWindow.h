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
	static int keyPressed;
	bool switchPressed,isWindowed,isCursorShow;
	HWND g_hWnd;
	MSG msg;
	JuenWindow();
	~JuenWindow();
	
	void InitializeWindow();

	bool WindowIsRunning();

	void CleanUpWindow();

	static JuenWindow* GetWindowInstance();
	static void ReleaseWindowInstance();
	void ClientResize(HWND hWnd, int nWidth, int nHeight);

	void SetSwitchValue(bool switchValue);
	bool GetSwitchValue();

	void SetCurrentWindow(bool newWinValue);
	bool GetCurrentWindow();
	//void setCurrentWindow(bool newWinValue);

	void SetShowCursor(bool newCursorValue);
	bool GetShowCursor();
	void ChangeCursor();
};

