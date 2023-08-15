#include "pch.h"
#include "GameEngine.h"
#include "DXContext.h"

GameEngine::GameEngine()
	: mbInit(false)
	, mInput()
	, mTime()
{
}

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!DXContext::init(hWnd, width, height, bWindowed, D3DDEVTYPE_HAL) ||
		!mInput.init(hInstance, hWnd))
	{
		return false;
	}

	mTime.init();

	return true;
}

void GameEngine::Release()
{
	mInput.release();
	DXContext::release();
}

void GameEngine::OnTick()
{
	// 성능 측정 시작
	mTime.beginTick();

	// Input Event
	mInput.update();

	// 성능 측정 종료
	mTime.endTick();
}

InputManager& GameEngine::GetInput()
{
	return mInput;
}

TimeManager& GameEngine::GetTime()
{
	return mTime;
}
