#pragma once
#include"JuenWindow.h"
#include <dinput.h>
#include"d3dx9.h"

class JuenInput
{
private:
	static JuenInput *instance;
	JuenInput();
public:
	HRESULT keyResult;
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
	LPDIRECTINPUTDEVICE8  dInputMouseDevice;
	BYTE  diKeys[256];
	DIMOUSESTATE mouseState;
	int prev_MouseState[3];
	D3DXVECTOR2 mousePos;

	static JuenInput* GetInputInstance();
	static void ReleaseInputInstance();
	bool AcceptKeyDown(int index);
	bool AcceptButtonDown(int index);
	void ReleaseInput();
	void UpdateInput();
	
};

