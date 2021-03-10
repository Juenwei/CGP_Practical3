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
	/*case WM_MOUSEMOVE:
		JuenWindow::mouseX = LOWORD(lParam);
		JuenWindow::mouseY = HIWORD(lParam);*/


		break;
	case WM_KEYUP:
		JuenWindow::keyPressed = 0;
		if (wParam == 84)
		{
		    myWindow->ChangeCursor();
		}
		break;
	case WM_KEYDOWN:
		JuenWindow::keyPressed = wParam;
		if (wParam == 27)
		{
			PostQuitMessage(0);
		}
		else if (wParam == 70)
		{
			SetCursor(LoadCursorFromFile("aero_link_l.cur"));
		}
	
		else if (wParam == 189)
		{
			myWindow->ChangeSpeed(-1);
		}
		else if (wParam == 187)
		{
			myWindow->ChangeSpeed(1);
		}
		else if(wParam == 81)
		{
			myWindow->RandomColor();
		}
		else if(wParam == 69)
		{
			//myWindow->SetSwitchValue(true);
		}

		std::cout << wParam << std::endl;
		break;
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Static initialization
int JuenWindow::keyPressed = 0;

JuenWindow *JuenWindow::instance = NULL;

JuenWindow::JuenWindow()
{
	
	hInstance = GetModuleHandle(NULL);
	g_hWnd = NULL;
	rgbValue[0] = 255;
	rgbValue[1] = 255;
	rgbValue[2] = 255;
	
	isCursorShow = true;
	speed = 2;
	switchPressed = false;
    keyPressed = 0;
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

void JuenWindow::ChangeRBGValue(int colorValue, int colorType)
{
	if (colorValue > 255)
		colorValue = 0;
	else
	{
		colorValue+=speed;
	}
	rgbValue[colorType] = colorValue;
}

void JuenWindow::ChangeSpeed(int speedValue)
{
	if (speed >= 0&&speed<10&&speedValue>0)
	{
		speed += speedValue;
	}
	else if (speed > 0 && speed <= 10 && speedValue<0)
	{
		speed += speedValue;
	}
}

void JuenWindow::RandomColor()
{
	
	for (int i = 0; i < 2; i++)
	{
		rgbValue[i] = rand() % 255;
	}
}

void JuenWindow::SetSwitchValue(bool switchValue)
{
	switchPressed = switchValue;
}

bool JuenWindow::GetSwitchValue()
{
	return switchPressed;
}

#pragma region SwitchingWindow


bool JuenWindow::GetCurrentWindow()
{
	return isWindowed;
}

void JuenWindow::SetCurrentWindow(bool newWinValue)
{
	isWindowed = newWinValue;
}

void JuenWindow::SetShowCursor(bool newCursorValue)
{
	isCursorShow = newCursorValue;
}
bool JuenWindow::GetShowCursor()
{
	return isCursorShow;
}
void JuenWindow::ChangeCursor()
{
	if (isCursorShow)
	{
		isCursorShow = false;
	}
	else
	{
		isCursorShow = true;
	}
	ShowCursor(isCursorShow);
}

#pragma endregion

void JuenWindow::ClientResize(HWND hWnd, int nWidth, int nHeight)
{
	RECT rcClient, rcWind;
	POINT ptDiff;
	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWind);
	ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
	ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;
	MoveWindow(hWnd, rcWind.left, rcWind.top, nWidth + ptDiff.x, nHeight + ptDiff.y, TRUE);
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

	
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "JuenWei's Window", WS_OVERLAPPEDWINDOW, 0, 100, WINSCREEN_WIDTH, WINSCREEN_HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);
}

bool JuenWindow::WindowIsRunning()
{
	//Game looping

	
	ZeroMemory(&msg, sizeof(msg));

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/

	//while (msg.message != WM_QUIT)//Check the window is exit ? if yes stop the game loop
	//{
		/*
			The if- version process one message per one iteration loop
			The while- version will clear the message queue before dealing with your own code.

			Another function is GetMessage.
			This function is not suitable for game, because it will block your program until it recieves a message.
			your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
			Suitable for event based program, such as bussiness app.
		*/
		//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//Check event 
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) break;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);//Send the key value
	}

		/*
			Write your code here...
			input
			update
			render graphics
		*/
	//}

	return msg.message != WM_QUIT;
}


void JuenWindow::CleanUpWindow()
{
	UnregisterClass(wndClass.lpszClassName, hInstance);
}