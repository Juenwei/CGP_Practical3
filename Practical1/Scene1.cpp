#include "Scene1.h"

Scene1::Scene1()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	myPlayer = myPlayer->GetPlayerInstance();
	myPlayer->setScenePointer(this);

	//Delete once use new 
	MapTile *maptile = new MapTile(D3DXVECTOR2(550.0f, 700.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(1024.0f, 64.0f),0.0f);//9 tiles
	maptile->settingGeneratePoint(9, D3DXVECTOR2(128.0f, 0.0f), D3DXVECTOR2(32.0f, 660.0f));
	MapTile *maptile1 = new MapTile(D3DXVECTOR2(0.0f, 350.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(64.0f, 768.0f), 1.57f);
	maptile1->settingGeneratePoint(6, D3DXVECTOR2(0.0f, 128.0f), D3DXVECTOR2(32.0f, 0.0f));
	MapTile *maptile2 = new MapTile(D3DXVECTOR2(1100.0f, 350.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(64.0f, 768.0f), -1.57f);
	maptile2->settingGeneratePoint(6, D3DXVECTOR2(0.0f, 128.0f), D3DXVECTOR2(1066.0f, 128.0f));

	mapTileList.push_back(maptile);
	mapTileList.push_back(maptile1);
	mapTileList.push_back(maptile2);

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

	for (int i = 0; i < mapTileList.size(); i++)
	{
		delete mapTileList[i];
		mapTileList[i] = NULL;
	}

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


