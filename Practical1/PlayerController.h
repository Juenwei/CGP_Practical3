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
	RECT characterRect;
	RECT sizeRect;
	D3DXVECTOR2 characterSize;
	int characterCurrentFrame;
	std::list<D3DXVECTOR2> trajecList;

	D3DXVECTOR2 trans, spriteCentre, scaling, scallingCentre;
	D3DXVECTOR2 inputAxis , playerVelocity ,jumpVector, posValue;
	D3DXMATRIX mat;
	int playerFaceDirX;
	float adjustedSpeed,speed;
	float animationDuration,animationTimer;

	//D3DXVECTOR2 position;
public:
	PlayerController();
	~PlayerController();
	void PlayerStart();
	void ReceiveInput();
	void PlayerMovement();
	void PlayerRender();
	void PlayerAnimation();
	void PlayerRelease();

	D3DXVECTOR2 GetPlayerPosistion();
	RECT GetPlayerRectSize();
	

	void Jump(float speed);
	D3DXVECTOR2 PlayJump();
	void ResolveCollision();
	bool isPlayerMoving;

};

