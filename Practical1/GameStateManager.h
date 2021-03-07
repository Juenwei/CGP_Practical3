#pragma once
#include"GameState.h"
#include<iostream>
#include"Scene1.h"
#include"Scene2.h"
#include<vector>

class GameStateManager
{
private:
	GameStateManager();
	~GameStateManager();
	static GameStateManager *instance;

public:
	GameState *currentGameState;
	std::vector<GameState*>gameStateList;
	enum GAMESTATESCENE
	{
		SCENE_1=0,
		SCENE_2=1
	};


	static GameStateManager*GetInstance();
	void ReleaseInstance();
	void ChangeGameState(int index);
	void Update();
	void Draw();
};
