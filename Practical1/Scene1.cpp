#include "Scene1.h"

Scene1::Scene1()
{
	myWindow = myWindow->GetWindowInstance();
	myGraphics = myGraphics->GetGraphicsInstance();
	myInput = myInput->GetInputInstance();

	texture = NULL;
	texture1 = NULL;
	texture2 = NULL;
	sprite = NULL;
	backSprite = NULL;
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	 

	D3DXCreateSprite(myGraphics->d3dDevice, &sprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/bg1.png", &texture);
	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);

	D3DXCreateSprite(myGraphics->d3dDevice, &backSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/pointer.png", &texture1);

	D3DXCreateSprite(myGraphics->d3dDevice, &backSprite);
	D3DXCreateTextureFromFile(myGraphics->d3dDevice, "Img/slime.png", &texture2);


	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 400;
	spriteRect.bottom = 300;

	pointerRect.left = 0;
	pointerRect.top = 0;
	pointerRect.right = 24;
	pointerRect.bottom = 24;

	characterRect.left = 0;
	characterRect.top = 0;
	characterRect.right = 32;
	characterRect.bottom = 32;

}

void Scene1::Update()
{
	if (myInput->AcceptKeyDown(DIK_LEFT))
	{
		std::cout << "LEFT" << std::endl;
		xPosValue -= 3;
	}
	else if (myInput->AcceptKeyDown(DIK_RIGHT))
	{
		std::cout << "RIGHT" << std::endl;
		xPosValue += 3;
	}
	else if (myInput->AcceptKeyDown(DIK_UP))
	{
		std::cout << "UP1" << std::endl;
		yPosValue -= 3;
	}
	else if (myInput->AcceptKeyDown(DIK_DOWN))
	{
		std::cout << "DOWN" << std::endl;
		yPosValue += 3;
	}
	else if (myInput->AcceptKeyDown(DIK_R))
	{
		myWindow->ChangeRBGValue(myWindow->rgbValue[0], 0);
		std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	}
	else if (myInput->AcceptKeyDown(DIK_G))
	{
		myWindow->ChangeRBGValue(myWindow->rgbValue[1], 1);
		std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	}
	else if (myInput->AcceptKeyDown(DIK_B))
	{
		myWindow->ChangeRBGValue(myWindow->rgbValue[2], 2);
		std::cout << "Current RGB(" << myWindow->rgbValue[0] << " , " << myWindow->rgbValue[1] << " , " << myWindow->rgbValue[2] << " , " << std::endl;

	}
	else if (myInput->AcceptButtonDown(0))
	{
		//Continous event
		std::cout << "Press" << std::endl;

		myInput->prev_MouseState[0] = 1;
	}
	else if (myInput->prev_MouseState[0] == 1)
	{
		//One time event
		std::cout << "Shoot" << std::endl;
		myInput->prev_MouseState[0] = 0;
	}
}

void Scene1::Draw()
{

	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	backSprite->Begin(D3DXSPRITE_ALPHABLEND);
	backSprite->Draw(texture1, &pointerRect, NULL, &D3DXVECTOR3(myInput->mousePos.x, myInput->mousePos.y, 0),
		D3DCOLOR_XRGB(myWindow->rgbValue[0], myWindow->rgbValue[1], myWindow->rgbValue[2]));
	backSprite->Draw(texture2, &characterRect, NULL, &D3DXVECTOR3(xPosValue, yPosValue, 0), D3DCOLOR_XRGB(255, 255, 255));
	//std::cout << "Slime pos : ("<<xPosValue<<" , " <<yPosValue<< std::endl;
	backSprite->End();

}

void Scene1::Release()
{
	sprite->Release();
	sprite = NULL;

	backSprite->Release();
	backSprite = NULL;

	texture->Release();
	texture = NULL;

	texture1->Release();
	texture1 = NULL;

	texture2->Release();
	texture2 = NULL;
}
