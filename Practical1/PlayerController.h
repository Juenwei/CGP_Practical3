#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"

class PlayerController
{
private:
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	enum class playerStatus
	{
		Active,
		Hide,
		Unactive
	};

	LPDIRECT3DTEXTURE9 playerTexture;
	LPD3DXSPRITE playerSprite;
	RECT characterRect;
	D3DXVECTOR2 characterSize;
	int characterCurrentFrame;

	D3DXVECTOR2 trans, spriteCentre, scaling, scallingCentre;
	D3DXVECTOR2 inputAxis , playerVelocity , posValue;
	D3DXMATRIX mat;
	int playerFaceDirX;
	float speed;
	float animationDuration,animationTimer;

	D3DXVECTOR2 position;
public:
	PlayerController();
	~PlayerController();
	void PlayerStart();
	void ReceiveInput();
	void PlayerMovement();
	void PlayerRender();
	void PlayerAnimation();
	void PlayerRelease();


};

