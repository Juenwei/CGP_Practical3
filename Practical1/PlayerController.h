#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include<list>

class PlayerController
{
private:
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	enum class playerStatus
	{
		Active,
		Hide
		//Unactive
	};

	LPDIRECT3DTEXTURE9 playerTexture;
	LPD3DXSPRITE playerSprite;
	RECT spriteCutRect;
	RECT colliderSizeRect;
	D3DXVECTOR2 characterSize, scaleFactor;
	int characterCurrentFrame;
	std::list<D3DXVECTOR2> trajecList;

	D3DXVECTOR3 characterCentre;
	D3DXVECTOR2 trans, scaling;
	D3DXVECTOR2 inputAxis , playerVelocity ,jumpVector, posValue;
	D3DXMATRIX mat;
	int playerFaceDirX;
	float adjustedSpeed,speed;
	float animationDuration,animationTimer;

	//D3DXVECTOR2 position;
public:
	PlayerController(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size, float speed);
	~PlayerController();
	void PlayerStart();
	void ReceiveInput();
	void PlayerMovement();
	void PlayerRender();
	void PlayerAnimation();
	void PlayerRelease();

	D3DXVECTOR2 GetPlayerPosistion();
	D3DXVECTOR3 GetPlayerCentre();
	RECT GetPlayerRectSize();
	

	void Jump(float speed);
	D3DXVECTOR2 PlayJump();
	void ResolveCollision();
	bool isPlayerMoving;

};

