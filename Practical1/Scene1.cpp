#include "Scene1.h"

Scene1::Scene1()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	myPlayer = myPlayer->GetPlayerInstance();
	myPlayer->setScenePointer(this);

	//Need to delete ? 
	MapTile *maptile = new MapTile(D3DXVECTOR2(300.0f, 600.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f, 32.0f));
	MapTile *maptile1 = new MapTile(D3DXVECTOR2(100.0f, 500.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f, 32.0f));
	//MapTile *maptile2 = new MapTile(D3DXVECTOR2(300.0f, 500.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f, 32.0f));

	mapTileList.push_back(maptile);
	mapTileList.push_back(maptile1);
	//mapTileList.push_back(maptile2);

	mapTileAmount = mapTileList.size();

	backTexture = NULL;
	texture1 = NULL;
	testIndex = 1;
	backSprite = NULL;
	trajectSprite = NULL;
	gravity = D3DXVECTOR2(0.0f, 10.0f);
	trajDotCenter = D3DXVECTOR3(16.0f, 16.0f, 0.0f);
	dotCuttingRect.top = 0;
	dotCuttingRect.left = 0;
	dotCuttingRect.bottom = 32;
	dotCuttingRect.right = 32;
	angleWithinRange = false;
	vOffsetDirection = D3DXVECTOR2(0, 0);
}

Scene1::~Scene1()
{
	//Destructor
}

void Scene1::Init()
{
	
	myPlayer->PlayerStart();
	//std::cout << "Size of Init : " << mapTileList.size() << std::endl;
	for (int i = 0; i < mapTileAmount; i++)
	{
		mapTileList[i]->mapStart();
	}
	
	D3DXCreateSprite(myGraphics->d3dDevice, &backSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &trajectSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/sciback.jpg", &backTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/pointer.png", &texture1);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slimeTraject.png", &trajectDotTex);
	//D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/enemyRobot.png", &enemyTex);


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
	RenewInput();
}

void Scene1::FixedUpdate()
{
	testIndex += 1;
	myPlayer->setIsApplyGravity(true);

	myPlayer->PlayerAnimation();
	myPlayer->PlayerMovement();
	
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
	
}

bool isPlayerStop = true;

//void Scene1::playerJump()
//{
//	//One time event
//	myPlayer->isPlayerMoving = true;
//	int counter = 0;
//	D3DXVECTOR2 gV = D3DXVECTOR2(0.0f, 0.0f);
//	estimatedPlayerPos = myPlayer->GetPlayerPosistion();
//	if (myPlayer->normDirectV.x >= 0)
//		myPlayer->playerFaceDirX = 1;
//	else
//		myPlayer->playerFaceDirX = -1;
//	vOffsetDirection = D3DXVECTOR2(myPlayer->normDirectV.x * 250.0f, myPlayer->normDirectV.y *150.0f);
//	bool continueCalculate = true;
//	myPlayer->setIsApplyGravity(false);
//	for (int i = 0; i < 60; i++)
//	{
//		vOffsetDirection.x *= 0.97f;
//		nextVelocity = D3DXVECTOR2(0, 0);
//		if (i > 29)
//		{
//			//myPlayer->setIsApplyGravity(true);
//			gV = D3DXVECTOR2(0, 15.0f);
//			vOffsetDirection += gV;
//		}
//		nextVelocity += (vOffsetDirection)/30;
//		estimatedPlayerPos += nextVelocity;
//		for (int x = 0; x < mapTileAmount; x++)
//		{
//			if (CollisionManager::CheckCollision(myPlayer->setCalculateCollision(estimatedPlayerPos), mapTileList[x]->getCollisionRect()) || estimatedPlayerPos.y > 700)
//			{
//				continueCalculate = false;
//				break;
//			}
//
//		}
//
//		if (continueCalculate)
//		{
//			//std::cout << "Push next pos : ( " << estimatedPlayerPos.x << " , " << estimatedPlayerPos.y << " ) " << std::endl;
//			myPlayer->trajecList.push_back(nextVelocity);
//
//		}
//		else
//		{
//			break;
//		}
//	}
//	
//	
//}

//Give up method 
//int Scene1::displayTrajectLine(D3DXVECTOR2 vOffsetDirection)
//{
//	int estimatedIndex = 0;
//	bool continueCalculate = true;
//	estimatedPlayerPos = myPlayer->GetPlayerPosistion();
//	for (int i = 0; i < 60; i++)
//	{
//		nextVelocity = D3DXVECTOR2(0, 0);
//		nextVelocity += vOffsetDirection;
//		for (int x = 0; x < mapTileAmount; x++)
//		{
//			if (CollisionManager::CheckCollision(myPlayer->setCalculateCollision(estimatedPlayerPos), mapTileList[x]->getCollisionRect()) || estimatedPlayerPos.y > 700)
//			{
//				continueCalculate = false;
//				break;
//			}
//		}
//
//		if (continueCalculate)
//		{
//			estimatedPlayerPos += nextVelocity;
//			if (i % 5 == 0)
//			{
//				trajectSprite->Begin(D3DXSPRITE_ALPHABLEND);
//				trajectSprite->Draw(trajectDotTex, &dotCuttingRect, &trajDotCenter, &D3DXVECTOR3(estimatedPlayerPos.x, estimatedPlayerPos.y, 0.0f), D3DCOLOR_XRGB(255, 255, 255));
//				trajectSprite->End();
//			}
//
//		}
//		else
//		{
//			estimatedIndex = i;
//			break;
//		}
//		estimatedIndex ++;
//	}
//	//Decide how many time loop 
//	return estimatedIndex;
//
//}

void Scene1::ChangePlayerState(int playerStateIndex)
{

}

D3DXVECTOR2 Scene1::getGravity()
{
	return gravity;
}

MapTile * Scene1::getMapTilePointer(int index)
{
	return mapTileList[index];
}

int Scene1::getSizeOfMapTileList()
{
	return mapTileList.size();
}

int Scene1::getTestIndex()
{
	return testIndex;
}

void Scene1::Draw()
{
	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	backSprite->Begin(D3DXSPRITE_ALPHABLEND);
	backSprite->Draw(backTexture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	backSprite->Draw(texture1, &pointerRect, NULL, &D3DXVECTOR3(myInput->mousePos.x, myInput->mousePos.y, 0),D3DCOLOR_XRGB(255, 255, 255));
	//backSprite->Draw(enemyTex, NULL, NULL, &D3DXVECTOR3(0.0f, 0.0f, 0), D3DCOLOR_XRGB(255, 255, 255));
	backSprite->End();

	
	for (int i = 0; i < mapTileAmount; i++)
	{
		mapTileList[i]->mapRender();
	}
	myPlayer->PlayerRender();


}

void Scene1::Release()
{

	trajectDotTex->Release();
	trajectDotTex = NULL;

	backTexture->Release();
	backTexture = NULL;

	//enemyTex->Release();
	//enemyTex = NULL;

	texture1->Release();
	texture1 = NULL;

	trajectSprite->Release();
	trajectSprite = NULL;

	backSprite->Release();
	backSprite = NULL;

	for (int i = 0; i < mapTileAmount; i++)
	{
		mapTileList[i]->mapRelease();
	}

	myPlayer->PlayerRelease();
	myPlayer->ReleasePlayerInstance();



}


