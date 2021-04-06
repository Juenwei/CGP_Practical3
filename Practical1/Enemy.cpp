#include "Enemy.h"

Enemy *Enemy::instance = NULL;


Enemy::Enemy()
{
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();
	//movingStateDuration = 2;
	animationDuration = 0.5f / 5;
	healthFont = NULL;
	enemySprite = NULL;
	enemyTexture = NULL;
	//EnemyColliderBox = NULL;

	enemyStatus[shootingState].shootingCooldown = 0.4f;
	enemyStatus[shootingState].stateTimer = 3.0f;
	enemyStatus[MoveShootingState].shootingCooldown = 0.6f;
	enemyStatus[MoveShootingState].stateTimer = 8.0f;

	enemySpeed = 250.0f;
	scaleFactor = D3DXVECTOR2(1.0f, 1.0f);
	enemyPosValue = D3DXVECTOR2(500.0f, 100.0f);
	enemySize = D3DXVECTOR2(102.4f, 128.0f);
	originPoint = D3DXVECTOR2(500.0f, 100.0f);
	targetPosition[0] = originPoint;
	targetPosition[1] = D3DXVECTOR2(900.0f, 100.0f);
	targetPosition[2] = D3DXVECTOR2(900.0f, 300.0f);
	targetPosition[3] = D3DXVECTOR2(900.0f, 600.0f);

	healthTextRect.left = -55;
	healthTextRect.top = -95;
	healthTextRect.right = 0;
	healthTextRect.bottom = 0;
	enemyHealthUIRect.left = 0;
	enemyHealthUIRect.top = 0;
	enemyHealthUIRect.right = 128;
	enemyHealthUIRect.bottom = 42;
	enemyCentre = D3DXVECTOR3(enemySize.x /2, enemySize.y / 2, 0.0f);
	oriSizeRect.left = 0;
	oriSizeRect.top = 0;
	oriSizeRect.right = 70.0f;
	oriSizeRect.bottom = 80.0f;
	
	//State Need to reset
	currentTargetPosIndex = 0;
	targetDirection = 1;
	isMoveActivate = true;
	enemyHealth = 100;
	amountLoop = 0;
}

Enemy::~Enemy()
{

}

Enemy *Enemy::GetEnemyInstance()
{
	if (!instance)
	{
		instance = new Enemy;
	}
	return instance;
}

void Enemy::ReleaseEnemyInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void Enemy::EnemyStart()
{
	D3DXCreateSprite(myGraphics->d3dDevice, &enemySprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/enemyRobot.png", &enemyTexture);
	//D3DXCreateLine(myGraphics->d3dDevice, &EnemyColliderBox);
	D3DXCreateFont(myGraphics->d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &healthFont);
}

void Enemy::EnemyUpdate()
{
	//Collision
	enemyColliderSizeRect = CollisionManager::CalculateCollision(enemyPosValue,
		oriSizeRect, D3DXVECTOR2(enemyCentre.x - 15.0f, enemyCentre.y - 30.0f));
	//CollisionManager::setCollisionBox(enemyPointArray, enemyColliderSizeRect);

	if (currentEnemyStatus == MoveShootingState && amountLoop < 3)
	{
		D3DXVECTOR2 tempOffset = targetPosition[currentTargetPosIndex] - enemyPosValue;
		D3DXVECTOR2 moveDirection;
		float length = D3DXVec2Length(&tempOffset);
		D3DXVec2Normalize(&moveDirection, &tempOffset);
		enemyPosValue += moveDirection * enemySpeed / 60.0f;
		if (length < 3)
		{
			currentTargetPosIndex += targetDirection;
			if (currentTargetPosIndex == 3)
			{
				targetDirection = -1;
			}
			else if (currentTargetPosIndex == 0)
			{
				amountLoop++;
				targetDirection = 1;
			}

		}
		std::cout << "Current Index : " << currentTargetPosIndex << std::endl;
	}
}

void Enemy::EnemyRender()
{
	enemySprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&enemyMat, NULL, 0.0, &scaleFactor, NULL, NULL, &enemyPosValue);
	enemySprite->SetTransform(&enemyMat);
	enemySprite->Draw(enemyTexture, &enemySpriteCutRect, &enemyCentre, NULL , D3DCOLOR_XRGB(255, 255, 255));
	D3DXVECTOR2 tempEnemyUIPos = enemyPosValue + D3DXVECTOR2(-64.0f, -100.0f);
	D3DXMatrixTransformation2D(&enemyMat, NULL, 0.0, NULL, NULL, 0.0, &tempEnemyUIPos);
	enemySprite->SetTransform(&enemyMat);
	enemySprite->Draw(enemyUITexture, &enemyHealthUIRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	D3DXMatrixTransformation2D(&enemyMat, NULL, 0.0, NULL, NULL, 0.0, &enemyPosValue);
	enemySprite->SetTransform(&enemyMat);
	std::string healthString = "Health : " + std::to_string(enemyHealth);
	healthFont->DrawText(enemySprite, healthString.c_str(), -1, &healthTextRect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	enemySprite->End();

	//CollisionManager::drawColliderBox(EnemyColliderBox, enemyPointArray, 5);

}

void Enemy::EnemyAnimation()
{
	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationDuration)
	{
		animationTimer -= animationDuration;
		enemyCurrentFrame++;
		enemyCurrentFrame %= 5;
	}

	//Update animation
	enemySpriteCutRect.left = enemySize.x*enemyCurrentFrame;
	enemySpriteCutRect.top = 0;
	enemySpriteCutRect.right = enemySpriteCutRect.left + enemySize.x;
	enemySpriteCutRect.bottom = 128;
}

void Enemy::EnemyRelease()
{
	//CollisionManager::releaseColliderBox(EnemyColliderBox);

	healthFont->Release();
	healthFont = NULL;

	enemyTexture->Release();
	enemyTexture = NULL;

	enemySprite->Release();
	enemySprite = NULL;
}

void Enemy::ResetEnemyValue()
{
	enemyHealth = 100;
	amountLoop == 0;
	enemyPosValue = D3DXVECTOR2(500.0f, 100.0f);
	originPoint = D3DXVECTOR2(500.0f, 100.0f);
	isMoveActivate = true;
	currentTargetPosIndex = 0;
}


RECT Enemy::getEnemyColliderRect()
{
	return enemyColliderSizeRect;
}

void Enemy::BulletCollide(float damage)
{
	std::cout << "Enemy get " << damage << " damage" << std::endl;
	enemyHealth -= damage;
}

void Enemy::ChangeEnemyState()
{
	//One time event
	if (currentEnemyStatus == shootingState)
	{
		currentEnemyStatus = MoveShootingState;
		isMoveActivate = true;
		amountLoop = 0;
	}
	else
	{
		currentEnemyStatus = shootingState;
		amountLoop = 0;
	}
}

D3DXVECTOR2 Enemy::GetEnemyPosistion()
{
	return enemyPosValue;
}

int Enemy::getCurrentEnemyState()
{
	return currentEnemyStatus;
}

int Enemy::getEnemyHealth()
{
	return enemyHealth;
}

void Enemy::SetEnemyUI(LPDIRECT3DTEXTURE9 UITexture)
{
	enemyUITexture = UITexture;
}
