#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"mapTile.h"
#include<list>

class Scene1;

class PlayerController
{
private:
	static PlayerController *instance;
	JuenGraphics *myGraphics;
	JuenInput*myInput;
	Scene1 *sceneInstance;

	enum PlayerStatus
	{
		groundState,
		wallState, //0
	}currentPStatus;

	struct PStatus {
		float spriteRotationRadian;
		int moveDikIndex;
		float minAngleClamp, maxAngleClamp;
		RECT colliderRect;
	};


	//Basic Sprite Setting
	LPDIRECT3DTEXTURE9 playerTexture,trajectDotTex;
	LPD3DXSPRITE playerSprite, trajectSprite;
	LPD3DXLINE playerLine;
	RECT spriteCutRect, trajDotCuttingRect;
	D3DXVECTOR2 characterSize, scaleFactor;
	D3DXVECTOR3 characterCentre, trajDotCenter;
	D3DXVECTOR2 scaling;
	float rotation;

	//Movement Setting
	D3DXVECTOR2 inputAxis, prev_PlayerVelocity, playerMoveVelocity, playerPosValue;
	D3DXMATRIX mat;
	float adjustedSpeed,speed;

	//Animation Setting
	int characterCurrentFrame;
	float animationDuration,animationTimer;

	//Collider Setting
	RECT oriSizeRect, colliderSizeRect;
	D3DXVECTOR2 playerPointArray[5];

	RECT oriSizeRect2, colliderSizeRect2;
	D3DXVECTOR2 playerPointArray2[5];
	D3DXVECTOR3 rect2Center;

	//Constructor
	PlayerController(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size, float speed);
	~PlayerController();

public:
	int playerFaceDirX;
	std::list<D3DXVECTOR2> trajecList;
	D3DXVECTOR2 normDirectV , totalVelocity;

	//int currentPlayerStatusIndex = 0;
	PStatus pStateType[2];

	//Condition & State
	bool isReleasedKey;
	bool isPlayerMoving;
	bool isPlayerFalling;
	bool isPlayerCollided;
	bool isShowingTrajectDot;

	//Singletlon method
	static PlayerController* GetPlayerInstance();
	static void ReleasePlayerInstance();

	//Basic method
	void PlayerStart();
	void ReceiveInput();
	void PlayerMovement();
	void PlayerRender();
	void PlayerAnimation();
	void PlayerRelease();

	//Trajectory
	void calNorDirection(D3DXVECTOR2 fromP, D3DXVECTOR2 toP);
	bool trajectoryAngleClamp();
	//D3DXVECTOR2 PlayJump();
	D3DXVECTOR2 falling();
	void playerJumpVer2();
	
	//collision method
	void ResolveCollision(RECT colliderRect);

	//ChangeState method
	void ChangePlayerState(int targetState);

	//Getter & Setter
	D3DXVECTOR2 GetPlayerPosistion();
	D3DXVECTOR3 GetPlayerCentre();
	

	RECT setCalculatePlayerCollision();
	
	void setIsApplyGravity(bool boolValue);
	void setScenePointer(Scene1 *scenePtr);
};

