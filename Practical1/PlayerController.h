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
		wallState,
	}currentPStatus;

	struct PStatus {
		//float spriteRotationRadian;
		int AngleClameType;
		//float minAngleClamp, maxAngleClamp;
		RECT colliderRect[2];
		D3DXVECTOR2 colliderSidePoint[4];
	};

	int tempPlayerStateIndex = 0;

	//Basic Sprite Setting
	LPDIRECT3DTEXTURE9 playerTexture,trajectDotTex;
	LPD3DXSPRITE playerSprite, trajectSprite;
	LPD3DXLINE playerLine;
	RECT spriteCutRect, trajDotCuttingRect;
	D3DXVECTOR2 characterSize, scaleFactor;
	D3DXVECTOR3 characterCentre, trajDotCenter;
	D3DXVECTOR2 scaling;
	float rotation;
	float minAngleClamp, maxAngleClamp;

	//Movement Setting
	D3DXVECTOR2 inputAxis, prev_PlayerVelocity, playerMoveVelocity, playerPosValue;
	D3DXMATRIX mat;
	float speed;

	//Animation Setting
	int characterCurrentFrame;
	float animationDuration,animationTimer;

	//Collider Setting
	RECT oriSizeRect, colliderSizeRect;
	D3DXVECTOR2 playerPointArray[5];

	RECT oriSizeOuterRect2, colliderSizeRect2;
	D3DXVECTOR2 playerPointArray2[5];
	D3DXVECTOR3 outerColliderRect2Center;


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
	bool isMoveKeyPressed;
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
	void ChangePlayerState(PlayerStatus targetState, float rotation, int mixAngle, int maxAngle);

	//Getter & Setter
	D3DXVECTOR2 GetPlayerPosistion();
	D3DXVECTOR3 GetPlayerCentre();
	

	RECT setCalculatePlayerCollision();
	
	void setIsApplyGravity(bool boolValue);
	void setScenePointer(Scene1 *scenePtr);
};

