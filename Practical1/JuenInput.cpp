#include "JuenInput.h"
#include<iostream>



JuenInput::JuenInput()
{
	JuenWindow*myWindow = myWindow->GetWindowInstance();
	//diKeys[256] = { 0 };
	DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	//Create keyboard device
	dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputKeyboardDevice->SetCooperativeLevel(JuenWindow::GetWindowInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputKeyboardDevice->Acquire();

	//Create mouse device
	dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	dInputMouseDevice->SetCooperativeLevel(JuenWindow::GetWindowInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	dInputMouseDevice->Acquire();
	
	mousePos.x = 0;
	mousePos.y = 0;

	ZeroMemory(diKeys, sizeof(diKeys));
	ZeroMemory(&mouseState, sizeof(mouseState));
	ZeroMemory(&prev_MouseState, sizeof(prev_MouseState));
	ZeroMemory(&prev_KeyState, sizeof(prev_KeyState));
}

JuenInput *JuenInput::instance = NULL;

JuenInput *JuenInput:: GetInputInstance()
{
	if (!instance)
	{
		instance = new JuenInput;

	}
	return instance;
}

void JuenInput::ReleaseInputInstance()
{

	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
	
}

bool JuenInput::AcceptKeyDown(int index)
{
	return diKeys[index] & 0x80;
}

//bool JuenInput::AcceptKeyUp(int index)
//{
//
//	return false;
//}

bool JuenInput::AcceptButtonDown(int index)
{
	return mouseState.rgbButtons[index] & 0x80;
}

void JuenInput::ReleaseInput()
{
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	dInput->Release();
	dInput = NULL;
}

void JuenInput::UpdateInput()
{
	
	keyResult = dInputKeyboardDevice->GetDeviceState(sizeof(diKeys), (LPVOID)&diKeys);
	if (FAILED(keyResult))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((keyResult == DIERR_INPUTLOST) || (keyResult == DIERR_NOTACQUIRED))
		{
			dInputKeyboardDevice->Acquire();
		}
		
	}
	keyResult = dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
	if (FAILED(keyResult))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((keyResult == DIERR_INPUTLOST) || (keyResult == DIERR_NOTACQUIRED))
		{
			dInputMouseDevice->Acquire();
		}

	}

	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	mousePos.x += mouseState.lX;
	mousePos.x = max(mousePos.x, 0);
	mousePos.x = min(mousePos.x, WINSCREEN_WIDTH);
	mousePos.y += mouseState.lY;
	mousePos.y = max(mousePos.y, 0);
	mousePos.y = min(mousePos.y, WINSCREEN_HEIGHT);
}
