#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"JuenInput.h"
class MapTile
{
private:
	JuenGraphics *myGraphics;
	JuenInput*myInput;
	
	LPDIRECT3DTEXTURE9 tileTexture, dotTexture;
	LPD3DXSPRITE tileSprite, dotSprite;
	RECT mapTileRect,sizeRect;
	D3DXVECTOR2 TileSize;

	D3DXVECTOR2 trans, spriteCentre, scaling, scallingCentre, dotTrans,dotCentre;
	
	D3DXMATRIX mat,dotMat;


public:
	MapTile (int posX ,int posY, float sizeX , float sizeY);
	~MapTile();
	void mapStart();
	void mapUpdate();
	void mapRender();
	void mapRelease();

	D3DXVECTOR2 GetMapPosistion();
	RECT GetMaprRectSize();

};

