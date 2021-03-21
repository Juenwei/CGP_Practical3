#include "PlayerController.h"


PlayerController::PlayerController(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size, float speed)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();


	playerTexture = NULL;
	playerSprite = NULL;
	prev_PlayerVelocity = D3DXVECTOR2(0, 0);
	isPlayerMoving = false;
	characterCurrentFrame = 0;
	for (int i = 0; i < 5; i++)
	{
		playerPointArray[i] = D3DXVECTOR2(0, 0);
	}

	characterSize.x = size.x;
	characterSize.y = size.y;
	scaleFactor.x = scale.x;
	scaleFactor.y = scale.y;
	oriSizeRect.top = 0, oriSizeRect.left = 0, oriSizeRect.bottom = 26, oriSizeRect.right = size.x;

	
	posValue = D3DXVECTOR2(pos.x, pos.y);
	jumpVelocity = D3DXVECTOR2(0, 0);
	characterCentre = D3DXVECTOR3(size.x / 2, size.y / 4, 0.0f);
	playerFaceDirX = 1;
	animationTimer = 0;
	animationDuration = 0.5f / 5;
	this->speed = speed;
	adjustedSpeed = this->speed / 60.0f;

}


PlayerController::~PlayerController()
{

}

PlayerController *PlayerController::instance = NULL;

PlayerController *PlayerController::GetPlayerInstance()
{
	if (!instance)
	{
		instance = new PlayerController(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f), D3DXVECTOR2(32.0f, 32.0f), 60.0f);

	}
	return instance;
}

void PlayerController::ReleasePlayerInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void PlayerController::PlayerStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &playerSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &playerTexture);
	D3DXCreateLine(myGraphics->d3dDevice, &playerLine);
	/*spriteCutRect.left = 0;
	spriteCutRect.top = 32;
	spriteCutRect.right = spriteCutRect.left + characterSize.x;
	spriteCutRect.bottom = spriteCutRect.top + characterSize.y;*/
}
void PlayerController::ReceiveInput()
{
	isPlayerMoving = false;
	inputAxis = D3DXVECTOR2(0, 0);
	if (myInput->AcceptKeyDown(DIK_LEFT))
	{
		//std::cout << "LEFT" << std::endl;
		inputAxis.x = -1;
		playerFaceDirX =-1;
		isPlayerMoving = true;
		
	}
	if (myInput->AcceptKeyDown(DIK_RIGHT))
	{
		//std::cout << "RIGHT" << std::endl;
		inputAxis.x = 1;
		playerFaceDirX = 1;
		isPlayerMoving = true;
	}
	if (myInput->AcceptKeyDown(DIK_UP))
	{
		//std::cout << "UP1" << std::endl;
		inputAxis.y = -1;
		isPlayerMoving = true;
	}
	if (myInput->AcceptKeyDown(DIK_DOWN))
	{
		//std::cout << "DOWN" << std::endl;
		inputAxis.y = 1;
		isPlayerMoving = true;
	}
	else if (myInput->AcceptKeyDown(DIK_P))
	{
		std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
		
	}

}
void PlayerController::PlayerMovement()
{
	//std::cout << " Is player move : " << isPlayerMoving << std::endl;
	CollisionManager::setCollisionBox(playerPointArray, getCalculateCollision());
	if (isPlayerMoving)
	{
		playerMoveVelocity = inputAxis * adjustedSpeed;
		//std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
		if (playerMoveVelocity != D3DXVECTOR2(0, 0))
		{
			prev_PlayerVelocity = playerMoveVelocity;
		}
	}
	else
	{
		jumpVelocity = D3DXVECTOR2(0, 0);
		playerMoveVelocity = D3DXVECTOR2(0, 0);
	}


	jumpVelocity = PlayJump();
	posValue += playerMoveVelocity + jumpVelocity;

	playerTrans = D3DXVECTOR2(posValue.x, posValue.y);
	scaling = D3DXVECTOR2(scaleFactor.x*playerFaceDirX, scaleFactor.y);
	float rotation = 0;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, rotation, &playerTrans);

	//std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
	//std::cout << "Scale : (" << scaling.x << " , " << scaling.y << " ) " << std::endl;
}

void PlayerController::PlayerRender() 
{
	playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(playerTexture, &spriteCutRect, &characterCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
	playerSprite->End();
	CollisionManager::drawColliderBox(playerLine, playerPointArray);
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
	spriteCutRect.left = characterSize.x*characterCurrentFrame;
	spriteCutRect.top = 32;
	spriteCutRect.right = spriteCutRect.left + characterSize.x;
	spriteCutRect.bottom = 64;

	//std::cout << "CF : " << characterCurrentFrame << std::endl;
	//std::cout << "RECT X : " << characterRect.left << " , " << characterRect.right << std::endl;
	//std::cout << "RECT Y TOP : " << characterRect.top << " , BOTTOM : " << characterRect.bottom << std::endl;
}


void PlayerController::PlayerRelease()
{
	CollisionManager::releaseColliderBox(playerLine);

	playerTexture->Release();
	playerTexture = NULL;

	playerSprite->Release();
	playerSprite = NULL;
}

void PlayerController::calNorDirection(D3DXVECTOR2 fromP, D3DXVECTOR2 toP)
{
	D3DXVECTOR2 dir,norDir;
	long int mag;

	dir = toP - fromP;
	//mag = D3DXVec2LengthSq(&dir);
	D3DXVec2Normalize(&norDir, &dir);
	normDirectV = norDir;
	std::cout << "Normalized vector X : " << norDir.x << "Normalized vector Y : " << norDir.y << std::endl;
	
}

D3DXVECTOR2 PlayerController::GetPlayerPosistion()
{
	return posValue;
}

D3DXVECTOR3 PlayerController::GetPlayerCentre()
{
	return characterCentre;
}

D3DXVECTOR2 PlayerController::PlayJump()
{
	D3DXVECTOR2 nextVelocity = D3DXVECTOR2(0, 0);
	if (!trajecList.empty())
	{
		//std::cout << "Play Jumps !! "<< std::endl;
		nextVelocity = trajecList.front();
		trajecList.pop_front();
		prev_PlayerVelocity = nextVelocity;
		if (trajecList.empty())
		{
			ResolveCollision();
		}
	}
	return nextVelocity;
}


void PlayerController::ResolveCollision()
{
	isPlayerMoving = false;
	posValue -= prev_PlayerVelocity;
	std::cout << "Resolving !! " << std::endl;
}

RECT PlayerController::getCalculateCollision()
{
	colliderSizeRect = CollisionManager::CalculateCollision(posValue,
		oriSizeRect, D3DXVECTOR2(characterCentre.x, characterCentre.y));
	return colliderSizeRect;
}

RECT PlayerController::setCalculateCollision(D3DXVECTOR2 pos)
{
	estimateRect = CollisionManager::CalculateCollision(pos, oriSizeRect, D3DXVECTOR2(characterCentre.x, characterCentre.y));
	return estimateRect;
}
