#include "mapTile.h"

MapTile::MapTile(int posX, int posY, float sizeX, float sizeY)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	tileTexture=NULL;
	tileSprite=NULL;
	dotSprite = NULL;
	mapTileRect.left = 0;
	mapTileRect.top = 0;
	mapTileRect.right = 256;
	mapTileRect.bottom = 256;
	scallingCentre = D3DXVECTOR2(mapTileRect.right / 2 * sizeX, mapTileRect.bottom / 2 * sizeY);
	spriteCentre = D3DXVECTOR2(mapTileRect.right / 2 * sizeX, mapTileRect.bottom / 2 * sizeY);
	trans = D3DXVECTOR2(posX, posY);
	TileSize=D3DXVECTOR2(sizeX,sizeY);

	sizeRect.top = 0, sizeRect.left = 0;
	sizeRect.bottom = mapTileRect.bottom*sizeX, sizeRect.right = mapTileRect.right*sizeY;
	
}

MapTile::~MapTile()
{

}

void MapTile::mapStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &tileSprite);
	D3DXCreateSprite(myGraphics->d3dDevice, &dotSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/Tile.png", &tileTexture);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/dot.png", &dotTexture);
	float rotation = 0;
	D3DXMatrixTransformation2D(&mat, &scallingCentre, 0.0, &TileSize, NULL, rotation, &trans);


	dotTrans = scallingCentre;
	dotCentre = D3DXVECTOR2(8, 8);
	D3DXMatrixTransformation2D(&dotMat, &dotCentre, 0.0, NULL, NULL, 0, &dotTrans);
	std::cout << "Centre pos : (" << scallingCentre.x << " , " << scallingCentre.y << std::endl;

}

void MapTile::mapUpdate()
{
}

void MapTile::mapRender()
{
	tileSprite->Begin(D3DXSPRITE_ALPHABLEND);
	tileSprite->SetTransform(&mat);
	tileSprite->Draw(tileTexture, &mapTileRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//std::cout << "Slime pos : ("<<xPosValue<<" , " <<yPosValue<< std::endl;
	tileSprite->End();

	dotSprite->Begin(D3DXSPRITE_ALPHABLEND);
	dotSprite->SetTransform(&dotMat);
	dotSprite->Draw(dotTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	dotSprite->End();

}

void MapTile::mapRelease()
{
	tileTexture->Release();
	tileTexture = NULL;

	dotTexture->Release();
	dotTexture = NULL;

	tileSprite->Release();
	tileSprite = NULL;

	dotSprite->Release();
	dotSprite = NULL;

}

D3DXVECTOR2 MapTile::GetMapPosistion()
{
	return D3DXVECTOR2(trans.x,trans.y);
}

RECT MapTile::GetMaprRectSize()
{
	return sizeRect;
}
