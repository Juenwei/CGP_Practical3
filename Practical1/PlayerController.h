#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"mapTile.h"
#include<list>

class PlayerController
{
private:
	static PlayerController *instance;
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	enum class playerStatus
	{
		Active,
		Hide
	};

	//Basic Sprite Setting
	LPDIRECT3DTEXTURE9 playerTexture;
	LPD3DXSPRITE playerSprite;
	LPD3DXLINE playerLine;
	RECT spriteCutRect;
	D3DXVECTOR2 characterSize, scaleFactor;
	D3DXVECTOR3 characterCentre;
	D3DXVECTOR2 scaling;

	//Movement Setting
	D3DXVECTOR2 inputAxis, prev_PlayerVelocity, playerMoveVelocity, posValue;
	D3DXMATRIX mat;
	float adjustedSpeed,speed;

	//Animation Setting
	int characterCurrentFrame;
	float animationDuration,animationTimer;

	//Collider Setting
	RECT oriSizeRect, colliderSizeRect, estimateRect;
	D3DXVECTOR2 playerPointArray[5];



public:
	int playerFaceDirX;
	std::list<D3DXVECTOR2> trajecList;
	bool isPlayerMoving;
	D3DXVECTOR2 normDirectV, jumpVelocity, playerTrans;

	//Singletlon method
	static PlayerController* GetPlayerInstance();
	static void ReleasePlayerInstance();
	//Constructor
	PlayerController(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size, float speed);
	~PlayerController();

	//Basic method
	void PlayerStart();
	void ReceiveInput();
	void PlayerMovement();
	void PlayerRender();
	void PlayerAnimation();
	void PlayerRelease();

	void calNorDirection(D3DXVECTOR2 fromP, D3DXVECTOR2 toP);
	D3DXVECTOR2 PlayJump();

	//collision method
	void ResolveCollision();

	//Getter
	D3DXVECTOR2 GetPlayerPosistion();
	D3DXVECTOR3 GetPlayerCentre();
	

	RECT getCalculateCollision();
	RECT setCalculateCollision(D3DXVECTOR2 pos);
	

};

