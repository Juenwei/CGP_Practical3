#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"PlayerController.h"
#include<list>

class Enemy
{
private:
	static Enemy *instance;
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	//enum EnemyStatus
	//{
	//	
	//}currentEnemyStatus;

	//Basic Sprite Setting
	LPDIRECT3DTEXTURE9 enemyTexture;
	LPD3DXSPRITE enemySprite;
	RECT enemySpriteCutRect;
	D3DXVECTOR2 scaleFactor, scaling;
	D3DXVECTOR3 enemyCentre;
	float rotation;

	//Movement Setting
	D3DXVECTOR2 enemyMoveVelocity, enemyPosValue;
	D3DXMATRIX enemyMat;
	float enemySpeed;

	//Animation Setting
	int enemyCurrentFrame;
	float animationDuration, animationTimer;

	//Collider Setting
	RECT oriSizeRect, colliderSizeRect;
	D3DXVECTOR2 enemyPointArray[5];

	//Constructor
	Enemy();
	~Enemy();

public:
	int enemyFaceDirX;
	D3DXVECTOR2 normDirectV;

	//Condition & State
	bool isEnemyCollided;

	//Singletlon method
	static Enemy* GetEnemyInstance();
	static void ReleaseEnemyInstance();

	//Basic method
	void EnemyStart();
	void EnemyMovement();
	void EnemyRender();
	void EnemyAnimation();
	void EnemyRelease();

	//Trajectory
	void calNorDirection(D3DXVECTOR2 fromP, D3DXVECTOR2 toP);

	//collision method
	void ResolveCollision(RECT colliderRect);

	//ChangeState method
	void ChangeEnemyState();

	//Getter & Setter
	D3DXVECTOR2 GetEnemyPosistion();
};

