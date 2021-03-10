#include "PlayerController.h"

PlayerController::PlayerController()
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	playerTexture = NULL;
	playerSprite = NULL;
	characterCurrentFrame = 0;
	characterSize.x = 32;
	characterSize.y = 32;
	xPosValue = 0, yPosValue = 0;
	playerFaceDirX = 1;
	animationTimer = 0;
	animationDuration = 0.5f / 5;
}
PlayerController::~PlayerController()
{

}
void PlayerController::PlayerStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &playerSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &playerTexture);
	characterRect.left = 0;
	characterRect.top = 32;
	characterRect.right = characterRect.left + characterSize.x;
	characterRect.bottom = characterRect.top + characterSize.y;
}
void PlayerController::ReceiveInput()
{
	if (myInput->AcceptKeyDown(DIK_LEFT))
	{
		//std::cout << "LEFT" << std::endl;
		xPosValue -= 3;
	
		playerFaceDirX =-1;
		
		
	}
	else if (myInput->AcceptKeyDown(DIK_RIGHT))
	{
		//std::cout << "RIGHT" << std::endl;
		xPosValue += 3;
		playerFaceDirX = 1;
		
	}
	else if (myInput->AcceptKeyDown(DIK_UP))
	{
		//std::cout << "UP1" << std::endl;
		yPosValue -= 3;
	}
	else if (myInput->AcceptKeyDown(DIK_DOWN))
	{
		//std::cout << "DOWN" << std::endl;
		yPosValue += 3;
	}
	

}
void PlayerController::PlayerMovement()
{
	// Texture being used is 32 by 32
	spriteCentre = D3DXVECTOR2(16.0f, 16.0f);
	scallingCentre= D3DXVECTOR2(16.0f, 16.0f);
	// Screen position of the sprite
	trans = D3DXVECTOR2(50.0f+ xPosValue, 80.0f+ yPosValue);
	// Rotate based on the time passed
	float rotation = 0;
	// Build our matrix to rotate, scale and position our sprite
	scaling = D3DXVECTOR2(2.0f*playerFaceDirX, 2.0f);
	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat, &scallingCentre, 0.0, &scaling, &spriteCentre, rotation, &trans);

	//std::cout << "Pos : (" << trans.x + xPosValue << " , " << trans.y + yPosValue << " ) " << std::endl;
	std::cout << "Scale : (" << scaling.x << " , " << scaling.y << " ) " << std::endl;
}

void PlayerController::PlayerRender() 
{
	playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(playerTexture, &characterRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//std::cout << "Slime pos : ("<<xPosValue<<" , " <<yPosValue<< std::endl;
	playerSprite->End();
}

void PlayerController::PlayerAnimation()
{
	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationDuration)
	{
		animationTimer -= animationDuration;
		characterCurrentFrame++;
		characterCurrentFrame %= 5;
	}
	
	//Update animation
	characterRect.left = characterSize.x*characterCurrentFrame;
	characterRect.top = 32;
	characterRect.right = characterRect.left + characterSize.x;
	characterRect.bottom = 64;

	//std::cout << "CF : " << characterCurrentFrame << std::endl;
	//std::cout << "RECT X : " << characterRect.left << " , " << characterRect.right << std::endl;
	//std::cout << "RECT Y TOP : " << characterRect.top << " , BOTTOM : " << characterRect.bottom << std::endl;
}


void PlayerController::PlayerRelease()
{
	playerTexture->Release();
	playerTexture = NULL;

	playerSprite->Release();
	playerSprite = NULL;
}