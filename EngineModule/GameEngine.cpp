#include "pch.h"
#include "GameEngine.h"
#include "DXContext.h"

GameEngine::GameEngine()
	: mbInit(false)
{
}

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	DXContext::init(hWnd, width, height, bWindowed, D3DDEVTYPE_HAL);

	return true;
}

void GameEngine::Release()
{
	DXContext::release();
}

void GameEngine::OnTick()
{
}
