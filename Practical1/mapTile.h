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
	RECT mapTileRect,mapColliderRect;
	D3DXVECTOR2 mapTileSize;

	D3DXVECTOR2 mapTileTrans, scaling, dotTrans;
	D3DXVECTOR3 mapCentre, dotCentre;
	
	D3DXMATRIX mat,dotMat;


public:
	MapTile(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size);
	~MapTile();
	void mapStart();
	void mapUpdate();
	void mapRender();
	void mapRelease();

	D3DXVECTOR2 GetMapPosistion();
	RECT GetMaprRectSize();
	D3DXVECTOR3 GetMapTileCentre();

};

