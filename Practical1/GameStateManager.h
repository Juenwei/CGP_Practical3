#pragma once
#include"GameState.h"
#include<iostream>
#include"Scene1.h"
#include"Scene2.h"
#include"JuenTimer.h"
#include"MainMenu.h"
#include<vector>



class GameStateManager
{
private:
	GameStateManager();
	~GameStateManager();
	static GameStateManager *instance;

public:
	GameState *currentGameState;
	JuenTimer* myTimer;
	std::vector<GameState*>gameStateList;
	enum GAMESTATESCENE
	{
		MENU = 0,
		SCENE_1 = 1,
	};
	static GameStateManager*GetInstance();
	void ReleaseInstance();
	void ChangeGameState(int index);
	void Update();
	void Draw();
};

