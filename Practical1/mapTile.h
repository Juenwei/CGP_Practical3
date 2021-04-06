#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"CollisionManager.h"
#include<vector>

class MapTile
{
private:
	JuenGraphics *myGraphics;
	enum MapTileType
	{
		verticalType,
		horizontalType
	};
	std::vector<D3DXVECTOR2> generatePointList;
	LPD3DXSPRITE tileSprite;
	LPDIRECT3DTEXTURE9 tileTexture;
	float rotation;
	int amountOfTile;
	D3DXVECTOR2 mapColliderTrans, mapTileScale, dotTrans;
	D3DXVECTOR3 mapCentre, dotCentre;
	D3DXMATRIX mapTileMat,dotMat;
	//Cutting Rect
	RECT mapTileCuttingRect; 
	//Collider Rect
	RECT oriColliderRect , mapColliderRect;
	//Collider Line
	//LPD3DXSPRITE dotSprite;
	//LPDIRECT3DTEXTURE9 dotTexture;
	//LPD3DXLINE mapLine;
	//D3DXVECTOR2 mapTilePointArray[5];


public:
	D3DXVECTOR2 mapSideCenterPoint[4];

	MapTile(D3DXVECTOR2 pos , D3DXVECTOR2 scale, D3DXVECTOR2 cuttingSpritesize,float rotation);
	~MapTile();
	void mapStart();
	void mapUpdate();
	void mapRender();
	void mapRelease();
	void settingGeneratePoint(int amountGenerate,D3DXVECTOR2 offsetRange, D3DXVECTOR2 initialPoint);

	//Getter & Setter
	RECT getCollisionRect();
	D3DXVECTOR2 GetMapPosistion();
	D3DXVECTOR3 GetMapTileCentre();

};

