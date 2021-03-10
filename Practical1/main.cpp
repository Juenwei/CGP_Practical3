#include"JuenWindow.h"
#include"JuenGraphics.h"
#include<stdio.h>
#include<d3d9.h>
#include<iostream>
#include<d3dx9.h>
#include <dinput.h>
#include"JuenInput.h"
#include"GameStateManager.h"

int main()
{
	JuenWindow *myWindow = myWindow->GetWindowInstance();
	myWindow->InitializeWindow();

	JuenGraphics *myGraphics = myGraphics->GetGraphicsInstance();
	JuenInput*myInput = myInput->GetInputInstance();
	GameStateManager *myGameStateManager = myGameStateManager->GetInstance();


	

	
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

		
		myGameStateManager->Update();
		
		myGraphics->BeginDraw();

		myGameStateManager->Draw();
	
		myGraphics->EndDraw();

	}
	myWindow->CleanUpWindow();

	
	myInput->ReleaseInput();

	myGraphics->ReleaseGraphicsInstance();

	myWindow->ReleaseWindowInstance();

	return 0;
}
