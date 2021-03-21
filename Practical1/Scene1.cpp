#include "Scene1.h"

Scene1::Scene1()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	//mycollision = new CollisionManager;

	myPlayer = myPlayer->GetPlayerInstance();

	MapTile *maptile = new MapTile(D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f, 32.0f));
	MapTile *maptile1 = new MapTile(D3DXVECTOR2(50.0f, 200.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f, 32.0f));
	mapTileList.push_back(maptile);
	mapTileList.push_back(maptile1);

	backTexture = NULL;
	texture1 = NULL;
	
	backSprite = NULL;
}

Scene1::~Scene1()
{
	//Destructor
}

void Scene1::Init()
{
	myPlayer->PlayerStart();
	//std::cout << "Size of Init : " << sizeof(mapTileList) << std::endl;
	for (int i = 0; i < 2; i++)
	{
		mapTileList[i]->mapStart();
	}
	
	D3DXCreateSprite(myGraphics->d3dDevice, &backSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/sciback.jpg", &backTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/pointer.png", &texture1);


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
	for (int i = 0; i <2; i++)
	{
		if (mycollision->CheckCollision(myPlayer->getCalculateCollision(), mapTileList[i]->getCollisionRect()))
		{
			myPlayer->ResolveCollision();
		}
	}

	
	myPlayer->PlayerAnimation();
	myPlayer->PlayerMovement();
	//mapt->mapUpdate();
	
}


void Scene1::RenewInput()
{
	myPlayer->ReceiveInput();

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
	else if (myInput->AcceptButtonDown(1))
	{
		myPlayer->calNorDirection(myPlayer->playerTrans, myInput->getMousePosition());
		myInput->prev_MouseState[1] = 1;
	}
	else if (myInput->prev_MouseState[1] == 1)
	{
		myInput->prev_MouseState[1] = 0;
		std::cout << "Space Key Pressed " << std::endl;
		playerJump();
	}
}

void Scene1::playerJump()
{
	//One time event
	myPlayer->isPlayerMoving = true;
	int counter = 0;
	D3DXVECTOR2 nextVelocity, vOffset, gravity;
	D3DXVECTOR2 estimatedPlayerPos = myPlayer->GetPlayerPosistion();
	gravity = D3DXVECTOR2(0, 8);
	if (myPlayer->normDirectV.x >= 0)
		myPlayer->playerFaceDirX = 1;
	else
		myPlayer->playerFaceDirX = -1;
	vOffset = D3DXVECTOR2(myPlayer->normDirectV.x * 150.0f, myPlayer->normDirectV.y * 150.0f);
	bool continueCalculate = true;
	for (int i = 0; i < 30; i++)
	{
	
		nextVelocity = D3DXVECTOR2(0, 0);
		if (i >= 13)
		{
			vOffset += gravity;
		}
		nextVelocity += vOffset / 30;
		//Check if next posistion with rect collided , if collide cut down the for loop , break 
		for (int i = 0; i < 2; i++)
		{
			if (CollisionManager::CheckCollision(myPlayer->setCalculateCollision(estimatedPlayerPos), mapTileList[i]->getCollisionRect()))
			{
				continueCalculate = false;
				std::cout << "STOP LOOPING !! " << std::endl;
			}

		}

		if (continueCalculate)
		{
			estimatedPlayerPos += nextVelocity;
			std::cout << "Push next pos : ( " << estimatedPlayerPos.x << " , " << estimatedPlayerPos.y << " ) " << std::endl;
			myPlayer->trajecList.push_back(nextVelocity);
		}
		else
		{
			break;
		}
		std::cout << "Counter : " << counter++ << std::endl;
	}
}

//MapTile * Scene1::getAllMapTileColllider(int index)
//{
//	//return mapTileList[index];
//	//return maptArray[index];
//}



void Scene1::Draw()
{
	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	backSprite->Begin(D3DXSPRITE_ALPHABLEND);
	backSprite->Draw(backTexture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	backSprite->Draw(texture1, &pointerRect, NULL, &D3DXVECTOR3(myInput->mousePos.x, myInput->mousePos.y, 0),D3DCOLOR_XRGB(255, 255, 255));
	backSprite->End();
	/*for (int i = 0; i < sizeof(maptArray); i++)
	{
		maptArray[i]->mapRender();
	}*/
	
	for (int i = 0; i < 2; i++)
	{
		mapTileList[i]->mapRender();
	}
	myPlayer->PlayerRender();



}

void Scene1::Release()
{
	delete mycollision;
	mycollision = NULL;

	backSprite->Release();
	backSprite = NULL;

	backTexture->Release();
	backTexture = NULL;

	texture1->Release();
	texture1 = NULL;

	for (int i = 0; i < 2; i++)
	{
		mapTileList[i]->mapRelease();
	}

	myPlayer->PlayerRelease();
	myPlayer->ReleasePlayerInstance();



}


