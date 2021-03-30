#pragma once
#include"JuenGraphics.h"
#include"JuenWindow.h"
#include"CollisionManager.h"
#include<vector>

class MapTile
{
private:
	JuenGraphics *myGraphics;
	//CollisionManager *mapCollider;
	
	enum MapTileType
	{
		verticalType,
		horizontalType
	};
	std::vector<D3DXVECTOR2> generatePointList;
	LPD3DXSPRITE tileSprite, dotSprite;
	LPDIRECT3DTEXTURE9 tileTexture, dotTexture;
	LPD3DXLINE mapLine;
	//Preset first then use dynamic array with pointer
	float rotation;
	int amountOfTile;
	D3DXVECTOR2 mapColliderTrans, mapTileScale, dotTrans;
	D3DXVECTOR3 mapCentre, dotCentre;
	D3DXMATRIX mapTileMat,dotMat;
	//Cutting Rect
	RECT mapTileCuttingRect; 
	//Collider Rect
	RECT oriColliderRect , mapColliderRect;
	//Collider Line , predefined first , one collider have 5 array value
	D3DXVECTOR2 mapTilePointArray[5];


public:
	D3DXVECTOR2 mapSideCenterPoint[4];

	MapTile(D3DXVECTOR2 pos , D3DXVECTOR2 scale, D3DXVECTOR2 cuttingSpritesize,float rotation);
	~MapTile();
	void mapStart();
	void mapUpdate();
	void mapRender();
	void mapRelease();
	void mapCollision();
	void settingGeneratePoint(int amountGenerate,D3DXVECTOR2 offsetRange, D3DXVECTOR2 initialPoint);
	//Getter & Setter
	RECT getCollisionRect();
	D3DXVECTOR2 GetMapPosistion();
	D3DXVECTOR3 GetMapTileCentre();

};

