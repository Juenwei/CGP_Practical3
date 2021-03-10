#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"

class PlayerController
{
private:
	JuenGraphics *myGraphics;
	JuenInput*myInput;

	LPDIRECT3DTEXTURE9 playerTexture;
	LPD3DXSPRITE playerSprite;
	RECT characterRect;
	D3DXVECTOR2 characterSize;
	int characterCurrentFrame;

	D3DXVECTOR2 trans, spriteCentre;
	D3DXVECTOR2 scaling,scallingCentre;
	D3DXMATRIX mat;
	int xPosValue, yPosValue, playerFaceDirX;
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

