#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"PlayerController.h"
#include"CollisionManager.h"
#include<list>

class Enemy
{
private:
	static Enemy *instance;
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	enum EnemyStatus
	{
		shootingState,
		MoveShootingState
	};
	int currentEnemyStatus;

	//Basic Sprite Setting
	LPDIRECT3DTEXTURE9 enemyTexture,enemyUITexture;
	LPD3DXSPRITE enemySprite;
	RECT enemySpriteCutRect, enemyHealthUIRect;
	D3DXVECTOR2 scaleFactor, enemySize;
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
	RECT oriSizeRect, enemyColliderSizeRect;

	//Collider box
	//LPD3DXLINE EnemyColliderBox;
	//D3DXVECTOR2 enemyPointArray[5];

	//Timer & State
	float moveTimeElapsed;// , movingStateDuration;
	D3DXVECTOR2 originPoint, targetPosition[4];
	int currentTargetPosIndex, targetDirection, amountLoop;

	//Health and damage
	int enemyHealth;
	LPD3DXFONT healthFont;
	RECT healthTextRect;

	//Constructor
	Enemy();
	~Enemy();

public:
	D3DXVECTOR2 normDirectV;
	struct EStatus {
		float shootingCooldown, stateTimer;
	};
	//Condition & State
	bool isEnemyCollided;
	bool isMoveActivate;
	EStatus enemyStatus[2];

	//Singletlon method
	static Enemy* GetEnemyInstance();
	static void ReleaseEnemyInstance();

	//Basic method
	void EnemyStart();
	void EnemyUpdate();
	void EnemyRender();
	void EnemyAnimation();
	void EnemyRelease();
	void ResetEnemyValue();

	//collision method
	RECT getEnemyColliderRect();
	void BulletCollide(float damage);

	//ChangeState method
	void ChangeEnemyState();

	//Getter & Setter
	D3DXVECTOR2 GetEnemyPosistion();
	int getCurrentEnemyState();
	int getEnemyHealth();
	void SetEnemyUI(LPDIRECT3DTEXTURE9 UITexture);
};

