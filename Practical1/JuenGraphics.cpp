#include "JuenGraphics.h"
#include "JuenWindow.h"

JuenGraphics::JuenGraphics()
{
	JuenWindow *myWindow = myWindow->GetWindowInstance();

	//	Define Direct3D 9.
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.

	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = WINSCREEN_WIDTH;
	d3dPP.BackBufferHeight = WINSCREEN_HEIGHT;
	d3dPP.hDeviceWindow = myWindow->GetWindowInstance()->g_hWnd;

	//Initialize window varaible
	//myWindow->SetCurrentWindow(d3dPP.Windowed);

	//	Create a Direct3D 9 device.
    hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, myWindow->GetWindowInstance()->g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	
}


JuenGraphics::~JuenGraphics()
{
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}


JuenGraphics *JuenGraphics::instance = NULL;

JuenGraphics *JuenGraphics::GetGraphicsInstance()
{
	if (!instance)
	{
		instance = new JuenGraphics;

	}
	return instance;
}

void JuenGraphics ::ReleaseGraphicsInstance()
{

	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}

}


void JuenGraphics::BeginDraw()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100,255, 120), 1.0f, 0);

	d3dDevice->BeginScene();
}

void JuenGraphics::EndDraw()
{
	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}
