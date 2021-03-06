#include"JuenWindow.h"
#include"JuenGraphics.h"
#include<stdio.h>
#include<d3d9.h>
#include<iostream>
#include<d3dx9.h>
#include <dinput.h>
#include"JuenInput.h"
#include"Scene1.h"

int main()
{
	JuenWindow *myWindow = myWindow->GetWindowInstance();
	myWindow->InitializeWindow();

	JuenGraphics *myGraphics = myGraphics->GetGraphicsInstance();
	JuenInput*myInput = myInput->GetInputInstance();

	/*LPDIRECTINPUT8 dInput;
	DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
	dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputKeyboardDevice->SetCooperativeLevel(myWindow->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputKeyboardDevice->Acquire();
	BYTE  diKeys[256];*/

	Scene1 *scene1 = new(Scene1);
	scene1->Init();

#pragma region OldInit
	//bool wScreenValue;

	//LPDIRECT3DTEXTURE9 texture = NULL, texture1 = NULL, texture2 = NULL;

	////LPDIRECT3DTEXTURE9 texture[2];
	//LPD3DXSPRITE sprite = NULL;
	//LPD3DXSPRITE sprite1 = NULL;

	////	Clear the back buffer.
	////d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(myWindow->rgbValue[0], myWindow->rgbValue[1], myWindow->rgbValue[2]), 1.0f, 0);
	///*for (int i = 0; i < sizeof(texture); i++)
	//{
	//	texture[i] = NULL;
	//}*/
	//
	//D3DXCreateSprite(myGraphics->d3dDevice, &sprite);
	//D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/bg1.png", &texture);
	////hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	////									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	////									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	////									NULL, NULL, &texture);

	//D3DXCreateSprite(myGraphics->d3dDevice, &sprite1);
	//D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/pointer.png", &texture1);

	//D3DXCreateSprite(myGraphics->d3dDevice, &sprite1);
	//D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &texture2);
	//
	//RECT spriteRect;
	//spriteRect.left = 0;
	//spriteRect.top = 0;
	//spriteRect.right = 400;
	//spriteRect.bottom = 300;
	//
	//RECT pointerRect;
	//pointerRect.left = 0;
	//pointerRect.top = 0;
	//pointerRect.right = 24;
	//pointerRect.bottom = 24;

	//RECT characterRect;
	//characterRect.left = 0;
	//characterRect.top = 0;
	//characterRect.right = 32;
	//characterRect.bottom = 32;

	//int localKeyValue, xPosValue = 0, yPosValue = 0;
	//int prev_MouseState[3] = { 0 };
#pragma endregion

#pragma region Commented stuff
	////	Define Direct3D 9.
	//IDirect3D9 * direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	////	Define how the screen presents.
	//D3DPRESENT_PARAMETERS d3dPP;
	//ZeroMemory(&d3dPP, sizeof(d3dPP));

	////	Refer to Direct3D 9 documentation for the meaning of the members.
	//d3dPP.Windowed = true;
	//d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	//d3dPP.BackBufferCount = 1;
	//d3dPP.BackBufferWidth = 400;
	//d3dPP.BackBufferHeight = 300;
	//d3dPP.hDeviceWindow = myWindow->GetWindowInstance()->g_hWnd;

	////Initialize window varaible
	//myWindow->SetCurrentWindow(d3dPP.Windowed);

	//IDirect3DDevice9 * d3dDevice;
	//	Create a Direct3D 9 device.



	//HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, myWindow->GetWindowInstance()->g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);


#pragma endregion

	
	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(myGraphics->hr))
		return 0;

	

	while (myWindow->WindowIsRunning())
	{
		
		myInput->UpdateInput();

#pragma region OldUpdate
		//if (myInput->AcceptKeyDown(DIK_LEFT))
	//{
	//	std::cout << "LEFT" << std::endl;
	//	xPosValue-=3;
	//}
	//else if (myInput->AcceptKeyDown(DIK_RIGHT))
	//{
	//	std::cout << "RIGHT" << std::endl;
	//	xPosValue += 3;
	//}
	//else if (myInput->AcceptKeyDown(DIK_UP))
	//{
	//	std::cout << "UP1" << std::endl;
	//	yPosValue -= 3;
	//}
	//else if (myInput->AcceptKeyDown(DIK_DOWN))
	//{
	//	std::cout << "DOWN" << std::endl;
	//    yPosValue += 3;
	//}
	//else if (myInput->AcceptKeyDown(DIK_R))
	//{
	//	myWindow->ChangeRBGValue(myWindow->rgbValue[0], 0);
	//	std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	//}
	//else if (myInput->AcceptKeyDown(DIK_G))
	//{
	//	myWindow->ChangeRBGValue(myWindow->rgbValue[1], 1);
	//	std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	//}
	//else if (myInput->AcceptKeyDown(DIK_B))
	//{
	//	myWindow->ChangeRBGValue(myWindow->rgbValue[2], 2);
	//	std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	//}
	//else if (myInput->AcceptButtonDown(0))
	//{
	//	//Continous event
	//	std::cout << "Press" << std::endl;

	//	myInput->prev_MouseState[0] = 1;
	//}
	//else if (myInput->prev_MouseState[0] == 1)
	//{
	//	//One time event
	//	std::cout << "Shoot" << std::endl;
	//	myInput->prev_MouseState[0] = 0;
	//}


	//Switch is pressed , no efficient , engine need to check statement every frame
	//if (myWindow->GetSwitchValue())
	//{
	//	//check of screen is window or full screen
	//	if (myWindow->GetCurrentWindow())
	//	{
	//		//is Windowed , so change to full screen
	//		myGraphics->d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	//		myGraphics->d3dPP.Windowed = false;
	//	}
	//	else
	//	{
	//		//is full screen , change to windowed
	//		myGraphics->d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	//		myGraphics->d3dPP.Windowed = true;
	//	}
	//	//reset switch
	//	myWindow->SetSwitchValue(false);
	//	//Update class variable
	//	myWindow->SetCurrentWindow(myGraphics->d3dPP.Windowed);
	//	myGraphics->d3dDevice->Reset(&myGraphics->d3dPP);
	//	//continue;
	//}
#pragma endregion

		
		scene1->Update();

		
		myGraphics->BeginDraw();

		scene1->Draw();


#pragma region OldDrawing
		////	Drawing.
		////	Specify alpha blend will ensure that the sprite will render the background with alpha.
		//sprite->Begin(D3DXSPRITE_ALPHABLEND);
		//sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		//sprite->End();

		//sprite1->Begin(D3DXSPRITE_ALPHABLEND);
		//sprite1->Draw(texture1, &pointerRect, NULL, &D3DXVECTOR3(myInput->mousePos.x, myInput->mousePos.y, 0),
		//	D3DCOLOR_XRGB(myWindow->rgbValue[0], myWindow->rgbValue[1], myWindow->rgbValue[2]));
		//sprite1->Draw(texture2, &characterRect,NULL, &D3DXVECTOR3(xPosValue, yPosValue, 0),D3DCOLOR_XRGB(255, 255, 255));
		////std::cout << "Slime pos : ("<<xPosValue<<" , " <<yPosValue<< std::endl;
		//sprite1->End();
#pragma endregion

		
		myGraphics->EndDraw();

	}
	myWindow->CleanUpWindow();

	scene1->Release();
	delete scene1;

	myInput->ReleaseInput();

	myGraphics->ReleaseGraphicsInstance();

	myWindow->ReleaseWindowInstance();

	return 0;
}
