#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
#include"CollisionManager.h"
#include<string>
#include<iostream>

class Button
{
private:
	JuenGraphics *myGraphics;
	JuenInput * myInput;
	LPD3DXSPRITE buttonSprite;
	LPDIRECT3DTEXTURE9 buttonTexture;
	LPD3DXFONT font;

	D3DXVECTOR2 buttonScale, buttonPos;
	D3DXVECTOR3 buttonCentre;
	D3DXMATRIX buttonMat;
	//Cutting Rect
	RECT buttonCuttingRect,textRect;
	//Collider Rect
	RECT oriColliderRect, buttonColliderRect;
	
	std::string buttonMsg;
	int rValue, gValue, bValue;
public:
	bool isOnClick,isPressed;
	Button(D3DXVECTOR2 pos,D3DXVECTOR2 buttonSize);
	~Button();
	void buttonStart(std::string buttonMsg);
	void buttonCollision(RECT mouseRect);
	void buttonRender();
	void buttonRelease();
	void resetButton();

};

