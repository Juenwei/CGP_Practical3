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
