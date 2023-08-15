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

	if (!DXContext::init(hWnd, width, height, bWindowed, D3DDEVTYPE_HAL))
	{
		return false;
	}

	mTime.init();

	return true;
}

void GameEngine::Release()
{
	DXContext::release();
}

void GameEngine::OnTick()
{
	// 성능 측정 시작
	mTime.beginTick();

	// 성능 측정 종료
	mTime.endTick();
}

TimeManager& GameEngine::GetTime()
{
	return mTime;
}
