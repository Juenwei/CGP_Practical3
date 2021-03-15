#include "PlayerController.h"

PlayerController::PlayerController()
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	playerTexture = NULL;
	playerSprite = NULL;
	isPlayerMoving = false;
	characterCurrentFrame = 0;
	characterSize.x = 32;
	characterSize.y = 32;
	sizeRect.top = 0, sizeRect.left = 0, sizeRect.bottom = characterSize.y, sizeRect.right = characterSize.x;

	posValue = D3DXVECTOR2(50, 50);
	jumpVector = D3DXVECTOR2(0, 0);
	spriteCentre = D3DXVECTOR2(16.0f, 16.0f);
	scallingCentre = D3DXVECTOR2(16.0f, 16.0f);
	playerFaceDirX = 1;
	animationTimer = 0;
	animationDuration = 0.5f / 5;
	speed = 80.0f;
	adjustedSpeed = speed / 60.0f;
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
	else if (myInput->AcceptKeyDown(DIK_SPACE))
	{
		myInput->prev_KeyState[DIK_SPACE] = 1;
	}
	else if (myInput->prev_KeyState[DIK_SPACE] == 1)
	{
		myInput->prev_KeyState[DIK_SPACE] = 0;
		std::cout << "Space Key Pressed " << std::endl;
		Jump(speed);
	}
	else if (myInput->AcceptKeyDown(DIK_P))
	{
		std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
		
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
	scaling = D3DXVECTOR2(2.0f*playerFaceDirX, 2.0f);
	float rotation = 0;
	D3DXMatrixTransformation2D(&mat, &scallingCentre, 0.0, &scaling, &spriteCentre, rotation, &trans);

	//std::cout << "Pos : (" << posValue.x << " , " << posValue.y << " ) " << std::endl;
	//std::cout << "Scale : (" << scaling.x << " , " << scaling.y << " ) " << std::endl;
}

void PlayerController::PlayerRender() 
{
	playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	playerSprite->SetTransform(&mat);
	playerSprite->Draw(playerTexture, &characterRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

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

D3DXVECTOR2 PlayerController::GetPlayerPosistion()
{
	return D3DXVECTOR2(posValue.x,posValue.y);
}

RECT PlayerController::GetPlayerRectSize()
{
	return sizeRect;
}

void PlayerController::Jump(float speed)
{
	//One time event
	int counter = 0;
	D3DXVECTOR2 nextPos, Direction, velocity, gravity;
	nextPos= D3DXVECTOR2(0, 0);
	gravity = D3DXVECTOR2(0, 8);
	Direction = D3DXVECTOR2(5 * adjustedSpeed*playerFaceDirX, -10);
	velocity = D3DXVECTOR2(1, 1);

	velocity = Direction;
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
