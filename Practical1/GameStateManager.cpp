#include "GameStateManager.h"

GameStateManager *GameStateManager::instance = 0;

GameStateManager::GameStateManager()
{
	Scene1 *scene1 = new Scene1();
	scene1->Init();
	Scene2 *scene2 = new Scene2();
	scene2->Init();

	gameStateList.push_back(scene1);
	gameStateList.push_back(scene2);

	currentGameState = scene1;
	myTimer = new(JuenTimer);
	myTimer->Init(60);

}

GameStateManager::~GameStateManager()
{
	delete myTimer;
	myTimer = NULL;
	for (int i = 0; i < sizeof(gameStateList); i++)
	{
		delete gameStateList[i];
		gameStateList[i] = NULL;
	}
}

GameStateManager * GameStateManager::GetInstance()
{
	if (!instance)
	{
		instance = new GameStateManager;

	}
	return instance;
}

void GameStateManager ::ReleaseInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void GameStateManager::ChangeGameState(int index)
{
	currentGameState = gameStateList[index];
}

void GameStateManager::Update()
{
	currentGameState->Update();
	int frameToUpdate = myTimer->FramesToUpdate();
	for (int i = 0; i < frameToUpdate; i++)
	{
		currentGameState->FixedUpdate();
	}

}

void GameStateManager::Draw()
{
	currentGameState->Draw();
}

