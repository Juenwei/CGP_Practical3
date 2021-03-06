#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include"resource.h"

class JuenWindow
{

private:
	static JuenWindow *instance;
	HINSTANCE hInstance;
	WNDCLASS wndClass;
	

public:
	static int keyPressed;
	//static int mouseX, mouseY;
	bool switchPressed,isWindowed,isCursorShow;
	int rgbValue[3],speed;
	//int rValue, gValue, bValue,speed;
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

	void ChangeRBGValue(int colorValue,int colorType);
	void ChangeSpeed(int speedValue);
	void RandomColor();

	void SetSwitchValue(bool switchValue);
	bool GetSwitchValue();

	void SetCurrentWindow(bool newWinValue);
	bool GetCurrentWindow();
	//void setCurrentWindow(bool newWinValue);

	void SetShowCursor(bool newCursorValue);
	bool GetShowCursor();
	void ChangeCursor();
};

