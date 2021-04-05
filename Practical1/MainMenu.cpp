#include "MainMenu.h"

MainMenu::MainMenu()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	startButton = new Button(D3DXVECTOR2(420.0f, 300.0f), D3DXVECTOR2(256.0f, 80.0f));
	tutorialButton = new Button(D3DXVECTOR2(420.0f, 400.0f), D3DXVECTOR2(256.0f, 80.0f));
	quitButton = new Button(D3DXVECTOR2(420.0f, 500.0f), D3DXVECTOR2(256.0f, 80.0f));
	closeTutorialButton = new Button(D3DXVECTOR2(700.0f, 500.0f), D3DXVECTOR2(256.0f, 80.0f));
	menuTexture = NULL;
	tutorialTexture = NULL;
	menuSprite = NULL;

	titleUIRect.left = 0;
	titleUIRect.top = 43;
	titleUIRect.right = 128;
	titleUIRect.bottom = 83;

	menuRect.left = 0;
	menuRect.top = 0;
	menuRect.right = 1920;
	menuRect.bottom = 1080;

	textRect.left = 100;
	textRect.top = 550;
	textRect.right = 150;
	textRect.bottom = 125;

	tutorialTexRect.left = 0;
	tutorialTexRect.top = 0;
	tutorialTexRect.right = 1080;
	tutorialTexRect.bottom = 700;
	LPD3DXFONT font = NULL;
	FMOD::System* system = NULL;
	
	//Mouse
	mouseColliderLine = NULL;
	mouseCenter = D3DXVECTOR2(16.0f, 16.0f);
	for (int i = 0; i < 5; i++)
	{
		mouseArray[i] = D3DXVECTOR2(0, 0);
	}
	oriMouseSizeRect.top = 0;
	oriMouseSizeRect.left = 0;
	oriMouseSizeRect.bottom = 32;
	oriMouseSizeRect.right = 32;
	isShowTutorial = false;
}

MainMenu::~MainMenu()
{
	SceneRelease();
}

void MainMenu::Init()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &menuSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/menu.jpg", &menuTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/yellowUI.png", &gameTitleTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/tutorial.png", &tutorialTexture);
	D3DXCreateLine(myGraphics->d3dDevice, &mouseColliderLine);
	D3DXCreateFont(myGraphics->d3dDevice, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	FMOD::System_Create(&system);
	system->init(512, FMOD_INIT_NORMAL, 0);

	system->createStream("Sound/menuSound.OGG", FMOD_DEFAULT, NULL, &sound);

	system->playSound(sound, NULL, false, &channel);// set paused to false
	sound->setMode(FMOD_LOOP_NORMAL);
	//Set back to 0.3f
	channel->setVolume(0.3f);
	colorDirection = 1;
	startButton->buttonStart("START");
	tutorialButton->buttonStart("TUTORIAL");
	quitButton->buttonStart("QUIT");
	closeTutorialButton->buttonStart("ClOSE");
}

void MainMenu::Update()
{
	if (myInput->AcceptKeyDown(DIK_RETURN))
	{

		myInput->prev_KeyState[DIK_RETURN] = 1;

	}
	else if (myInput->prev_KeyState[DIK_RETURN] == 1)
	{
		myInput->prev_KeyState[DIK_RETURN] = 0;
		channel->setPaused(true);
		GameStateManager::GetInstance()->ChangeGameState(GameStateManager::SCENE_1);

	}
	if (myInput->AcceptKeyDown(DIK_T))
	{

		myInput->prev_KeyState[DIK_T] = 1;

	}
	else if (myInput->prev_KeyState[DIK_T] == 1)
	{
		myInput->prev_KeyState[DIK_T] = 0;
		if (isShowTutorial)
			isShowTutorial = false;
		else
			isShowTutorial = true;

	}
	if (startButton->isOnClick)
	{
		startButton->resetButton();
		channel->setPaused(true);
		GameStateManager::GetInstance()->ChangeGameState(GameStateManager::SCENE_1);
	}
	if (tutorialButton->isOnClick)
	{
		tutorialButton->resetButton();
		if (isShowTutorial)
			isShowTutorial = false;
		else
			isShowTutorial = true;
	}
	if (quitButton->isOnClick)
	{
		quitButton->resetButton();
		myWindow->quitProgram();

	}
	if (closeTutorialButton->isOnClick)
	{
		closeTutorialButton->resetButton();
		isShowTutorial = false;
	}
	mouseRect = CollisionManager::CalculateCollision(myInput->getMousePosition(), oriMouseSizeRect, mouseCenter);
	CollisionManager::setCollisionBox(mouseArray, mouseRect);
	if (!isShowTutorial)
	{
		startButton->buttonCollision(mouseRect);
		tutorialButton->buttonCollision(mouseRect);
		quitButton->buttonCollision(mouseRect);
	}
	else
	{
		closeTutorialButton->buttonCollision(mouseRect);
	}

}

void MainMenu::FixedUpdate()
{
	if (redIndex < 254) 
	{
		redIndex += 60.0f/ 60.0f;
	}
	else if (redIndex > 40 && greenIndex < 254)
	{
		greenIndex += 60.0f / 60.0f;
		blueIndex += 60.0f / 60.0f;
	}
	else if (greenIndex > 100 && blueIndex < 254)
	{
		blueIndex += 60.0f / 60.0f;
	}
	else
	{
		redIndex = 0.0f;
		greenIndex = 0.0f;
		blueIndex = 0.0f;
	}
	
}

void MainMenu::Draw()
{
	
	if (isShowTutorial)
	{
		menuSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMatrixTransformation2D(&MenuMat, NULL, 0.0, NULL, NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
		menuSprite->SetTransform(&MenuMat);
		menuSprite->Draw(tutorialTexture, &tutorialTexRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		menuSprite->End();
		closeTutorialButton->buttonRender();
	}
	else
	{
		menuSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMatrixTransformation2D(&MenuMat, NULL, 0.0, NULL, NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
		menuSprite->SetTransform(&MenuMat);
		menuSprite->Draw(menuTexture, &menuRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		font->DrawText(menuSprite, "Press Enter to Play , Press T for tutorial", -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

		D3DXMatrixTransformation2D(&MenuMat, NULL, 0.0, &D3DXVECTOR2(2.5f, 2.0f), NULL, NULL, &D3DXVECTOR2(100.0f, 20.0f));
		menuSprite->SetTransform(&MenuMat);
		menuSprite->Draw(gameTitleTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		D3DXMatrixTransformation2D(&MenuMat, NULL, 0.0, &D3DXVECTOR2(2.0f, 2.0f), NULL, NULL, &D3DXVECTOR2(220.0f, 100.0f));
		menuSprite->SetTransform(&MenuMat);
		font->DrawText(menuSprite, "RPS Duel", -1, NULL, DT_NOCLIP, D3DCOLOR_XRGB(redIndex, greenIndex, blueIndex));
		menuSprite->End();
		startButton->buttonRender();
		tutorialButton->buttonRender();
		quitButton->buttonRender();
	}
	CollisionManager::drawColliderBox(mouseColliderLine, mouseArray, 5);
}

void MainMenu::SceneRelease()
{
	font->Release();
	font = NULL;

	mouseColliderLine->Release();
	mouseColliderLine = NULL;

	CollisionManager::releaseColliderBox(mouseColliderLine);


	startButton->buttonRelease();
	delete startButton;
	startButton = NULL;

	tutorialButton->buttonRelease();
	delete tutorialButton;
	tutorialButton = NULL;

	quitButton->buttonRelease();
	delete quitButton;
	quitButton = NULL;

	closeTutorialButton->buttonRelease();
	delete closeTutorialButton;
	closeTutorialButton = NULL;

	tutorialTexture->Release();
	tutorialTexture = NULL;

	menuSprite->Release();
	menuSprite = NULL;

	menuTexture->Release();
	menuTexture = NULL;

	system->release();
	system = NULL;

	sound->release();
	sound = NULL;

}

void MainMenu::RenewInput()
{
}
