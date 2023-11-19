#include "Scene1.h"

Scene1::Scene1()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	myPlayer = myPlayer->GetPlayerInstance();
	myPlayer->setScenePointer(this);
	myPoolManager->GetPoolManagerInstance();
	myEnemy = myEnemy->GetEnemyInstance();
	
	FMOD::System* system = NULL;

	//Delete once use new 
	MapTile *maptile = new MapTile(D3DXVECTOR2(550.0f, 700.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(1024.0f, 64.0f),0.0f);//9 tiles
	maptile->settingGeneratePoint(9, D3DXVECTOR2(128.0f, 0.0f), D3DXVECTOR2(32.0f, 660.0f));
	MapTile *maptile1 = new MapTile(D3DXVECTOR2(0.0f, 350.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(64.0f, 768.0f), 1.57f);
	maptile1->settingGeneratePoint(6, D3DXVECTOR2(0.0f, 128.0f), D3DXVECTOR2(32.0f, 0.0f));
	MapTile *maptile2 = new MapTile(D3DXVECTOR2(1100.0f, 350.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(64.0f, 768.0f), -1.57f);
	maptile2->settingGeneratePoint(6, D3DXVECTOR2(0.0f, 128.0f), D3DXVECTOR2(1066.0f, 128.0f));
	//128 X 64
	MapTile *maptile3 = new MapTile(D3DXVECTOR2(300.0f, 400.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f, 192.0f), 0.0f);
	maptile3->settingGeneratePoint(3, D3DXVECTOR2(0.0f, 64.0f), D3DXVECTOR2(238.0f, 300.0f));
	MapTile *maptile4 = new MapTile(D3DXVECTOR2(650.0f, 400.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(128.0f, 192.0f), 0.0f);
	maptile4->settingGeneratePoint(3, D3DXVECTOR2(0.0f, 64.0f), D3DXVECTOR2(588.0f, 300.0f));
	BGScaling = D3DXVECTOR2(2.7f, 2.7f);
	mapTileList.push_back(maptile);
	mapTileList.push_back(maptile1);
	mapTileList.push_back(maptile2);
	mapTileList.push_back(maptile3);
	mapTileList.push_back(maptile4);

	backTexture = NULL;
	backSprite = NULL;
	trajectSprite = NULL;
	bulletTexture = NULL;
	bulletSprite = NULL;
	//bulletColliderline = NULL;
	winScreenTex = NULL;
	loseScreenTex = NULL;
	endGameFont = NULL;
	UItexture = NULL;
	//State
	isGamePaused = false;
	isVictory = false;
	isGameOver = false;

	gravity = D3DXVECTOR2(0.0f, 10.0f);
	trajDotCenter = D3DXVECTOR3(16.0f, 16.0f, 0.0f);
	mouseCursorRect.top = 0;
	mouseCursorRect.left = 0;
	mouseCursorRect.bottom = 32;
	mouseCursorRect.right = 32;
	angleWithinRange = false;
	vOffsetDirection = D3DXVECTOR2(0, 0);

	//Bullet
	pBulletRect.left = 4;
	pBulletRect.top = 0;
	pBulletRect.right = 36;
	pBulletRect.bottom = 32;
	eBulletRect.top = 0;
	eBulletRect.left = 76;
	eBulletRect.bottom = 32;
	eBulletRect.right = 108;

	//UI
	endGameScreenRect.left = 120;
	endGameScreenRect.top = 0;
	endGameScreenRect.right = 1280;
	endGameScreenRect.bottom = 700;
	endScreenTextRect.left = 200;
	endScreenTextRect.top = 550;
	endScreenTextRect.right = 150;
	endScreenTextRect.bottom = 125;
	//Enemy
	currentEnemyShootTime = 0.0f;
	currentEnemyStateTime = 0.0f;
	
}

Scene1::~Scene1()
{
	//Destructor
	SceneRelease();
}

void Scene1::Init()
{
	//Set the State
	isGamePaused = false;
	isVictory = false;
	isGameOver = false;
	FMOD::System_Create(&system);
	system->init(512, FMOD_INIT_NORMAL, 0);

	system->createStream("Sound/inGameSound.OGG", FMOD_DEFAULT, NULL, &bgSound);
	system->createSound("Sound/bulletSound.WAV", FMOD_DEFAULT, NULL, &bulletSound);

	bgSound->setMode(FMOD_LOOP_NORMAL);
	system->playSound(bgSound, NULL, false, &bgChannel);// set paused to false
	
	//Reset back to 0.1 & 0.3
	bgChannel->setVolume(0.3f);
	bulletChannel->setVolume(0.0f);

	myPlayer->PlayerStart();
	for (int i = 0; i < mapTileList.size(); i++)
	{
		mapTileList[i]->mapStart();
	}
	myEnemy->EnemyStart();

	D3DXCreateSprite(myGraphics->d3dDevice, &backSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &trajectSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &bulletSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/sciback.jpg", &backTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slimeTraject.png", &trajectDotTex);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/bullet.png", &bulletTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/victory1.jpg", &winScreenTex);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/gameover1.jpg", &loseScreenTex);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/orangeUI.png", &UItexture);
	D3DXCreateFont(myGraphics->d3dDevice, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Courier New", &endGameFont);

	//D3DXCreateLine(myGraphics->d3dDevice, &bulletColliderline);

	myPlayer->SetPlayerUI(UItexture);
	myEnemy->SetEnemyUI(UItexture);

	backGroundRect.left = 0;
	backGroundRect.top = 0;
	backGroundRect.right = 512;
	backGroundRect.bottom = 256;
	
}

void Scene1::Update()
{
	system->update();
	RenewInput();
	if (myPlayer->getPlayerHealth() <= 0)
	{
		isGamePaused = true;
		isGameOver = true;
		std::cout << "You are Dead , Game Over" << std::endl;
	}
	else if (myEnemy->getEnemyHealth() <= 0)
	{
		isGamePaused = true;
		isVictory = true;
		std::cout << "Enemy dead , Victory" << std::endl;
	}
	

	if (isGamePaused)
	{
		if (myInput->AcceptKeyDown(DIK_RETURN))
		{
			myInput->prev_KeyState[DIK_RETURN] = 1;

		}
		else if (myInput->prev_KeyState[DIK_RETURN] == 1)
		{
			myInput->prev_KeyState[DIK_RETURN] = 0;
			ResetScene();
			bgChannel->setPaused(true);
			GameStateManager::GetInstance()->ChangeGameState(GameStateManager::MENU);

		}
		return;
	}
	for (int i = 0; i < inUsingBulletList.size(); i++)
	{
		if (inUsingBulletList[i]->isBulletUsing)
		{
			inUsingBulletList[i]->BulletUpdate();
		}
		else
		{
			inUsingBulletList.erase(inUsingBulletList.begin() + i);
			break;
		}
	}

	
}

void Scene1::FixedUpdate()
{
	//std::cout << "Pool Size : " << myPoolManager->poolList.size() << std::endl;
	if (isGamePaused)
	{
		return;
	}
	myPlayer->PlayerTimer();
	myPlayer->setIsApplyGravity(true);
	myPlayer->PlayerAnimation();
	myPlayer->PlayerMovement();
	EnemyStateMachine();
	myEnemy->EnemyUpdate();
	myEnemy->EnemyAnimation();
	//myButton->buttonCollision();
	
}


void Scene1::RenewInput()
{
	//System Key
	//In game action Key
	if (isGamePaused)
	{
		return;
	}
	myPlayer->ReceiveInput();
	if (myInput->AcceptButtonDown(0)&&myPlayer->getPlayerShooting())
	{
		myInput->prev_MouseState[0] = 1;
	}
	else if (myInput->prev_MouseState[0] == 1)
	{
		myInput->prev_MouseState[0] = 0;
		myPlayer->ResetShootTimer();
		system->playSound(bulletSound, NULL, false, &bulletChannel);
		Bullet *tempBullet = myPoolManager->PullBulletFromPool();
		tempBullet->BulletStart(bulletTexture, pBulletRect, 400.0f);
		tempBullet->setBulletToObject(myPlayer->GetPlayerPosistion(),myInput->getMousePosition(),true);
		inUsingBulletList.push_back(tempBullet);
		

	}
	
	
}

void Scene1::ResetScene()
{
	//One time event
	for (int i = 0; i < inUsingBulletList.size(); i++)
	{
		inUsingBulletList[i]->BulletHide();
	}
	inUsingBulletList.clear();
	isGamePaused = false;
	isGameOver = false;
	isVictory = false;
	myPlayer->ResetPlayerValue();
	myEnemy->ResetEnemyValue();
}


void Scene1::EnemyStateMachine()
{
	currentEnemyStateTime += (1 / 60.0f);
	
	if (currentEnemyStateTime <= myEnemy->enemyStatus[myEnemy->getCurrentEnemyState()].stateTimer)
	{
		if (myEnemy->getCurrentEnemyState() == 0)
		{
			currentEnemyShootTime += (1 / 60.0f);
			if (currentEnemyShootTime >= myEnemy->enemyStatus[0].shootingCooldown)
			{
				BasicShootingStyle();
				currentEnemyShootTime -= myEnemy->enemyStatus[0].shootingCooldown;
			}
		}
		else if (myEnemy->getCurrentEnemyState() == 1)
		{
			currentEnemyShootTime += (1 / 60.0f);
			if (currentEnemyShootTime >= myEnemy->enemyStatus[1].shootingCooldown)
			{
				TripleShootingStyle();
				currentEnemyShootTime -= myEnemy->enemyStatus[1].shootingCooldown;
			}
		}
	}
	else
	{
		std::cout << "State Time exceed , change state" << std::endl;
		myEnemy->ChangeEnemyState();
		currentEnemyShootTime = 0.0f;
		currentEnemyStateTime = 0.0f;
	}
}

void Scene1::BasicShootingStyle()
{
	if (myEnemy->getEnemyHealth() <= 50)
	{
		D3DXVECTOR2 tempVector1 = myEnemy->GetEnemyPosistion();
		D3DXVECTOR2 tempVector2 = myPlayer->GetPlayerPosistion();
		tempVector1 -= D3DXVECTOR2(32.0f, 32.0f);
		tempVector2 -= D3DXVECTOR2(64.0f, 64.0f);
		for (int i = 0; i < 3; i++)
		{
			Bullet *tempBullet = myPoolManager->PullBulletFromPool();
			tempBullet->BulletStart(bulletTexture, eBulletRect, 250.0f);
			tempBullet->setBulletToObject(tempVector1, tempVector2, false);
			inUsingBulletList.push_back(tempBullet);
			tempVector1.x += 32.0f;
			tempVector1.y += 32.0f;
			tempVector2.x += 64.0f;
			tempVector2.y += 64.0f;
		}
	}
	else
	{
		Bullet *tempBullet = myPoolManager->PullBulletFromPool();
		tempBullet->BulletStart(bulletTexture, eBulletRect, 250.0f);
		tempBullet->setBulletToObject(myEnemy->GetEnemyPosistion(), myPlayer->GetPlayerPosistion(), false);
		inUsingBulletList.push_back(tempBullet);
	}
	system->playSound(bulletSound, NULL, false, &bulletChannel);
}

void Scene1::TripleShootingStyle()
{
	D3DXVECTOR2 tempVector1 = myEnemy->GetEnemyPosistion() - D3DXVECTOR2(0.0f, 32.0f);
	D3DXVECTOR2 tempVector2 = myEnemy->GetEnemyPosistion() - D3DXVECTOR2(1.0f, 32.0f);
	for (int i = 0; i < 3; i++)
	{
		Bullet *tempBullet = myPoolManager->PullBulletFromPool();
		tempBullet->BulletStart(bulletTexture, eBulletRect, 250.0f);
		tempBullet->setBulletToObject(tempVector1, tempVector2, false);
		inUsingBulletList.push_back(tempBullet);
		tempVector1.y += 32.0f;
		tempVector2.y += 32.0f;
	}
	system->playSound(bulletSound, NULL, false, &bulletChannel);
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


void Scene1::Draw()
{
	if (isGamePaused)
	{
		//Win and Lose
		/*std::cout << "IsGamePause : " << isGamePaused << std::endl;
		std::cout << "IsGameOver : " << isGameOver << std::endl;
		std::cout << "IsGamPause : " << isVictory << std::endl;*/

		backSprite->Begin(D3DXSPRITE_ALPHABLEND);
		if (isGameOver)
		{
			D3DXMatrixTransformation2D(&backGMat, NULL, 0.0, NULL, NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
			backSprite->SetTransform(&backGMat);
			backSprite->Draw(loseScreenTex, &endGameScreenRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
		else if (isVictory)
		{
			D3DXMatrixTransformation2D(&backGMat, NULL, 0.0, NULL, NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
			backSprite->SetTransform(&backGMat);
			backSprite->Draw(winScreenTex, &endGameScreenRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
		D3DXMatrixTransformation2D(&backGMat, NULL, 0.0, NULL, NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
		backSprite->SetTransform(&backGMat);
		endGameFont->DrawText(backSprite, "Press Enter to Back to Menu", -1, &endScreenTextRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		backSprite->End();
		return;
	}
	backSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&backGMat, NULL, 0.0, &BGScaling, NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
	backSprite->SetTransform(&backGMat);
	backSprite->Draw(backTexture, &backGroundRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	backSprite->End();
	for (int i = 0; i < mapTileList.size(); i++)
	{
		mapTileList[i]->mapRender();
	}
	myPlayer->PlayerRender();
	myEnemy->EnemyRender();
	backSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&cursorMat, NULL, 0.0, &D3DXVECTOR2(1.0f, 1.0f), NULL, NULL, &D3DXVECTOR2(myInput->mousePos.x, myInput->mousePos.y));
	backSprite->SetTransform(&cursorMat);
	backSprite->Draw(trajectDotTex, &mouseCursorRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	backSprite->End();
	for (int i = 0; i < inUsingBulletList.size(); i++)
	{
		//Implement Load the tex and sprite by using pass parameter
		inUsingBulletList[i]->BulletRender(bulletSprite);
	}

}

void Scene1::SceneRelease()
{
	myEnemy->EnemyRelease();
	myEnemy->ReleaseEnemyInstance();

	myPlayer->PlayerRelease();
	myPlayer->ReleasePlayerInstance();

	myPoolManager->ClearPool();
	myPoolManager->ReleasePoolManagerInstance();

	for (int i = 0; i < mapTileList.size(); i++)
	{
		mapTileList[i]->mapRelease();
		delete mapTileList[i];
		mapTileList[i] = NULL;
	}

	winScreenTex->Release();
	winScreenTex = NULL;

	loseScreenTex->Release();
	loseScreenTex = NULL;

	trajectDotTex->Release();
	trajectDotTex = NULL;

	backTexture->Release();
	backTexture = NULL;

	bulletTexture->Release();
	bulletTexture = NULL;

	bulletSprite->Release();
	bulletSprite = NULL;

	UItexture->Release();
	UItexture = NULL;

	endGameFont->Release();
	endGameFont = NULL;

	trajectSprite->Release();
	trajectSprite = NULL;

	backSprite->Release();
	backSprite = NULL;

	bgSound->release();
	bgSound = NULL;

	bulletSound->release();
	bulletSound = NULL;

	system->release();
	system = NULL;

}


