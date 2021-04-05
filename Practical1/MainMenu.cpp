#include "MainMenu.h"

MainMenu::MainMenu()
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	menuTexture = NULL;
	menuSprite = NULL;

	titleUIRect.left = 0;
	titleUIRect.top = 43;
	titleUIRect.right = 128;
	titleUIRect.bottom = 83;

	LPD3DXFONT font = NULL;
	FMOD::System* system = NULL;
	//ZeroMemory(&prev_keyState, sizeof(prev_keyState));

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

	menuRect.left = 0;
	menuRect.top = 0;
	menuRect.right = 1920;
	menuRect.bottom = 1080;

	textRect.left = 100;
	textRect.top = 550;
	textRect.right = 150;
	textRect.bottom = 125;

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
		std::cout << "Menu to scene1" << std::endl;
		GameStateManager::GetInstance()->ChangeGameState(GameStateManager::SCENE_1);

	}
}

void MainMenu::FixedUpdate()
{
}

void MainMenu::Draw()
{
	menuSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&MenuMat, NULL, 0.0, NULL, NULL, NULL, &D3DXVECTOR2(0.0f, 0.0f));
	menuSprite->SetTransform(&MenuMat);
	menuSprite->Draw(menuTexture, &menuRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(menuSprite, "Press Enter to Play , Press T for tutorial", -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMatrixTransformation2D(&MenuMat, NULL, 0.0, &D3DXVECTOR2(2.0f, 2.0f), NULL, NULL, &D3DXVECTOR2(200.0f, 100.0f));
	menuSprite->SetTransform(&MenuMat);
	menuSprite->Draw(gameTitleTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	menuSprite->End();
}

void MainMenu::SceneRelease()
{
	font->Release();
	font = NULL;

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
