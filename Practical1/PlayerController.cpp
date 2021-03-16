#include "PlayerController.h"

PlayerController::PlayerController(D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 size, float speed)
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	playerTexture = NULL;
	playerSprite = NULL;
	isPlayerMoving = false;
	characterCurrentFrame = 0;
	characterSize.x = size.x;
	characterSize.y = size.y;
	scaleFactor.x = scale.x;
	scaleFactor.y = scale.y;
	colliderSizeRect.top = 0, colliderSizeRect.left = 0, colliderSizeRect.bottom = 26, colliderSizeRect.right = size.x;

	
	posValue = D3DXVECTOR2(pos.x, pos.y);
	jumpVector = D3DXVECTOR2(0, 0);
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
void PlayerController::PlayerStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &playerSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &playerTexture);
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
	else if (myInput->AcceptKeyDown(DIK_RIGHT))
	{
		//std::cout << "RIGHT" << std::endl;
		inputAxis.x = 1;
		playerFaceDirX = 1;
		isPlayerMoving = true;
	}
	else if (myInput->AcceptKeyDown(DIK_UP))
	{
		//std::cout << "UP1" << std::endl;
		inputAxis.y = -1;
		isPlayerMoving = true;
	}
	else if (myInput->AcceptKeyDown(DIK_DOWN))
	{
		//std::cout << "DOWN" << std::endl;
		inputAxis.y = 1;
		isPlayerMoving = true;
	}
	/*else if (myInput->AcceptKeyDown(DIK_SPACE))
	{
		myInput->prev_KeyState[DIK_SPACE] = 1;
	}
	else if (myInput->prev_KeyState[DIK_SPACE] == 1)
	{
		myInput->prev_KeyState[DIK_SPACE] = 0;
		std::cout << "Space Key Pressed " << std::endl;
		Jump(speed);
	}*/
	else if (myInput->AcceptKeyDown(DIK_P))
	{
		std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
		
	}
	else if (myInput->AcceptButtonDown(1))
	{
		calNorDirection(trans,myInput->getMousePosition());
		myInput->prev_MouseState[1] = 1;
	}
	else if (myInput->prev_MouseState[1] == 1)
	{
		myInput->prev_MouseState[1] = 0;
		std::cout << "Space Key Pressed " << std::endl;
		Jump(speed);
	}
	
	

}
void PlayerController::PlayerMovement()
{
	playerVelocity = D3DXVECTOR2(0, 0);
	jumpVector = D3DXVECTOR2(0, 0);
	if (isPlayerMoving)
	{
		playerVelocity = inputAxis * adjustedSpeed;
		std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
	}


	jumpVector = PlayJump();
	posValue+= playerVelocity + jumpVector;

	trans = D3DXVECTOR2(posValue.x, posValue.y);
	scaling = D3DXVECTOR2(scaleFactor.x*playerFaceDirX, scaleFactor.y);
	float rotation = 0;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, rotation, &trans);

	//std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
	//std::cout << "Scale : (" << scaling.x << " , " << scaling.y << " ) " << std::endl;
}

void PlayerController::PlayerRender() 
{
	playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(playerTexture, &spriteCutRect, &characterCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));

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
	//std::cout << "Magnitude : " << mag << std::endl;
	//std::cout << "Normalized vector X : " << norDir.x << "Normalized vector Y : " << norDir.y << std::endl;
	
}

D3DXVECTOR2 PlayerController::GetPlayerPosistion()
{
	//return D3DXVECTOR2(posValue.x + characterCentre.x, posValue.y + characterCentre.y);
	return D3DXVECTOR2(posValue.x, posValue.y);
}

D3DXVECTOR3 PlayerController::GetPlayerCentre()
{
	return characterCentre;
}

RECT PlayerController::GetPlayerRectSize()
{
	return colliderSizeRect;
}

void PlayerController::Jump(float speed)
{
	//One time event
	int counter = 0;
	D3DXVECTOR2 nextPos,velocity, gravity;
	nextPos= D3DXVECTOR2(0, 0);
	gravity = D3DXVECTOR2(0, 8);

	velocity = D3DXVECTOR2(normDirectV.x * 30.0f, normDirectV.y * 25.0f);
	for (int i = 0; i < 30; i++)
	{
		if (i >= 15)
		{
			velocity += gravity;
		}
		nextPos += velocity/50;
		
		trajecList.push_back(nextPos);
		std::cout << "Counter : " << counter++ << std::endl;
	}
	std::cout << "Jump injected !! " << std::endl;
}

D3DXVECTOR2 PlayerController::PlayJump()
{
	D3DXVECTOR2 nextPos = D3DXVECTOR2(0, 0);
	if (!trajecList.empty())
	{
		std::cout << "Play Jumps !! "<< std::endl;
		nextPos = trajecList.front();
		trajecList.pop_front();
	}
	return nextPos;
}

void PlayerController::ResolveCollision()
{
	isPlayerMoving = false;
	posValue -= playerVelocity;
}
