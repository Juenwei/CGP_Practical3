#include "Scene1.h"

Scene1::Scene1()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	player = new(PlayerController);
	mapt = new MapTile(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f,32.0f));

	backTexture = NULL;
	texture1 = NULL;
	
	backSprite = NULL;
	characterCurrentFrame = 0;
	
	line = NULL;
}

Scene1::~Scene1()
{
	//Destructor
}

void Scene1::Init()
{
	player->PlayerStart();
	mapt->mapStart();
	//D3DXCreateSprite(myGraphics->d3dDevice, &playerSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &backSprite);

	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/sciback.jpg", &backTexture);
	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/pointer.png", &texture1);

	D3DXCreateLine(myGraphics->d3dDevice, &line);


	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 512;
	spriteRect.bottom = 256;

	pointerRect.left = 0;
	pointerRect.top = 0;
	pointerRect.right = 24;
	pointerRect.bottom = 24;



	

}

void Scene1::Update()
{
	

}

void Scene1::FixedUpdate()
{

	RenewInput();
	if (CheckCollision(player->GetPlayerPosistion(),player->GetPlayerRectSize(),mapt->GetMapPosistion(),mapt->GetMaprRectSize()))
	{
		player->ResolveCollision();
	}
	player->PlayerAnimation();
	player->PlayerMovement();
	//mapt->mapUpdate();
	
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
		myInput->prev_KeyState[DIK_F1] = 1;

	}
	else if (myInput->prev_KeyState[DIK_F1] == 1)
	{
		myInput->prev_KeyState[DIK_F1] = 0;
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

bool Scene1::CheckCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2)
{
	rect1.right = pos1.x + rect1.right - rect1.left-player->GetPlayerCentre().x;
	rect1.left = pos1.x - player->GetPlayerCentre().x;
	rect1.bottom = pos1.y + rect1.bottom - rect1.top - player->GetPlayerCentre().y;
	rect1.top = pos1.y - player->GetPlayerCentre().y;

	rect2.right = rect2.right - rect2.left + pos2.x-mapt->GetMapTileCentre().x;
	rect2.left = pos2.x - mapt->GetMapTileCentre().x;
	rect2.bottom = rect2.bottom - rect2.top + pos2.y - mapt->GetMapTileCentre().y;
	rect2.top = pos2.y - mapt->GetMapTileCentre().y;

	playerVertices[0] = D3DXVECTOR2(rect1.left, rect1.top);
	playerVertices[1] = D3DXVECTOR2(rect1.right, rect1.top);
	playerVertices[2] = D3DXVECTOR2(rect1.right, rect1.bottom);
	playerVertices[3] = D3DXVECTOR2(rect1.left, rect1.bottom);
	playerVertices[4] = D3DXVECTOR2(rect1.left, rect1.top);

	mapVertices[0] = D3DXVECTOR2(rect2.left, rect2.top);
	mapVertices[1] = D3DXVECTOR2(rect2.right, rect2.top);
	mapVertices[2] = D3DXVECTOR2(rect2.right, rect2.bottom);
	mapVertices[3] = D3DXVECTOR2(rect2.left, rect2.bottom);
	mapVertices[4] = D3DXVECTOR2(rect2.left, rect2.top);

	if (rect1.bottom < rect2.top) return false;

	if (rect1.top > rect2.bottom) return false;

	if (rect1.right < rect2.left) return false;

	if (rect1.left > rect2.right) return false;

	std::cout << "Collided" << std::endl;

	return true;
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
	mapt->mapRender();

	line->Begin();

	line->Draw(playerVertices, 5, D3DCOLOR_XRGB(100, 255, 120));
	line->Draw(mapVertices, 5, D3DCOLOR_XRGB(100, 255, 120));

	line->End();

}

void Scene1::Release()
{
	backSprite->Release();
	backSprite = NULL;

	/*playerSprite->Release();
	playerSprite = NULL;*/

	line->Release();
	line = NULL;

	backTexture->Release();
	backTexture = NULL;

	texture1->Release();
	texture1 = NULL;

	player->PlayerRelease();
	mapt->mapRelease();
	/*playerTexture->Release();
	playerTexture = NULL;*/
}


