#include "Scene1.h"

Scene1::Scene1()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	player = new(PlayerController);

	backTexture = NULL;
	texture1 = NULL;
	playerTexture = NULL;
	playerSprite = NULL;
	backSprite = NULL;
	characterCurrentFrame = 0;
	
	ZeroMemory(&prev_keyState, sizeof(prev_keyState));
}

Scene1::~Scene1()
{
	//Destructor
}

void Scene1::Init()
{
	player->PlayerStart();
	//D3DXCreateSprite(myGraphics->d3dDevice, &playerSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &backSprite);

	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/sciback1.jpg", &backTexture);
	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/pointer.png", &texture1);

	//D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &playerTexture);


	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 512;
	spriteRect.bottom = 256;

	pointerRect.left = 0;
	pointerRect.top = 0;
	pointerRect.right = 24;
	pointerRect.bottom = 24;

	/*characterSize.x = 32;
	characterSize.y = 32;

	characterRect.left = 0;
	characterRect.top = 32;
	characterRect.right = characterRect.left + characterSize.x;
	characterRect.bottom = characterRect.top + characterSize.y;*/



	

}

void Scene1::Update()
{


}

void Scene1::FixedUpdate()
{
	RenewInput();
	player->PlayerAnimation();
	player->PlayerMovement();
	//// Texture being used is 64 by 64:
	//spriteCentre = D3DXVECTOR2(32.0f, 32.0f);
	//// Screen position of the sprite
	//trans = D3DXVECTOR2(50.0f, 80.0f);
	//// Rotate based on the time passed
	//float rotation = 0;
	//// Build our matrix to rotate, scale and position our sprite
	//scaling = D3DXVECTOR2(2.0f, 2.0f);
	//// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	//D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);
}


void Scene1::RenewInput()
{/*
	if (myInput->AcceptKeyDown(DIK_LEFT))
	{
		std::cout << "LEFT" << std::endl;
		xPosValue -= 3;
	}
	else if (myInput->AcceptKeyDown(DIK_RIGHT))
	{
		std::cout << "RIGHT" << std::endl;
		xPosValue += 3;
	}
	else if (myInput->AcceptKeyDown(DIK_UP))
	{
		std::cout << "UP1" << std::endl;
		yPosValue -= 3;
	}
	else if (myInput->AcceptKeyDown(DIK_DOWN))
	{
		std::cout << "DOWN" << std::endl;
		yPosValue += 3;
	}*/
	player->ReceiveInput();

	if (myInput->AcceptKeyDown(DIK_F1))
	{
		prev_keyState[0] = 1;

	}
	else if (prev_keyState[0] == 1)
	{
		prev_keyState[0] = 0;
		std::cout << "Change Scene" << std::endl;
		GameStateManager::GetInstance()->ChangeGameState(GameStateManager::SCENE_2);

	}
	else if (myInput->AcceptKeyDown(DIK_R))
	{
		myWindow->ChangeRBGValue(myWindow->rgbValue[0], 0);
		std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	}
	else if (myInput->AcceptKeyDown(DIK_G))
	{
		myWindow->ChangeRBGValue(myWindow->rgbValue[1], 1);
		std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	}
	else if (myInput->AcceptKeyDown(DIK_B))
	{
		myWindow->ChangeRBGValue(myWindow->rgbValue[2], 2);
		std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	}
	else if (myInput->AcceptButtonDown(0))
	{
		//Continous event
		std::cout << "Press" << std::endl;

		myInput->prev_MouseState[0] = 1;
	}
	else if (myInput->prev_MouseState[0] == 1)
	{
		//One time event
		std::cout << "Shoot" << std::endl;
		myInput->prev_MouseState[0] = 0;
	}
}


void Scene1::Draw()
{
	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	backSprite->Begin(D3DXSPRITE_ALPHABLEND);
	backSprite->Draw(backTexture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	backSprite->Draw(texture1, &pointerRect, NULL, &D3DXVECTOR3(myInput->mousePos.x, myInput->mousePos.y, 0),
		D3DCOLOR_XRGB(myWindow->rgbValue[0], myWindow->rgbValue[1], myWindow->rgbValue[2]));
	backSprite->End();


	player->PlayerRender();

	//playerSprite ->Begin(D3DXSPRITE_ALPHABLEND);
	//playerSprite->SetTransform(&mat);
	//playerSprite->Draw(playerTexture, &characterRect, NULL, &D3DXVECTOR3(xPosValue, yPosValue, 0), D3DCOLOR_XRGB(255, 255, 255));
	////std::cout << "Slime pos : ("<<xPosValue<<" , " <<yPosValue<< std::endl;
	//playerSprite->End();

}

void Scene1::Release()
{


	backSprite->Release();
	backSprite = NULL;

	/*playerSprite->Release();
	playerSprite = NULL;*/

	backTexture->Release();
	backTexture = NULL;

	texture1->Release();
	texture1 = NULL;

	player->PlayerRelease();
	/*playerTexture->Release();
	playerTexture = NULL;*/
}


