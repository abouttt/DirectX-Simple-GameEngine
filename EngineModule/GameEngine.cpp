#include "pch.h"
#include "GameEngine.h"

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

	if (!mRenderer.init(hWnd, width, height, bWindowed) ||
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
	mRenderer.release();
}

void GameEngine::OnTick()
{
	// 성능 측정 시작
	mTime.beginTick();

	// Input Event
	mInput.update();

	// Game Logic
	
	// Scene Rendering
	mRenderer.preRender();
	mRenderer.render();
	mRenderer.drawUI();
	mRenderer.postRender();

	// Decommissioning
	
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
