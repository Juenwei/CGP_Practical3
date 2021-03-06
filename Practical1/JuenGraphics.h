#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include<iostream>
#include"resource.h"
#include<d3d9.h>
#include<d3dx9.h>
class JuenGraphics
{
private:
	static JuenGraphics *instance;
	JuenGraphics();
	~JuenGraphics();
	
public :
	static JuenGraphics* GetGraphicsInstance();
	static void ReleaseGraphicsInstance();
	IDirect3D9 * direct3D9;
	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3DDevice9 * d3dDevice;
	HRESULT hr;

	void BeginDraw();
	void EndDraw();
	
};

