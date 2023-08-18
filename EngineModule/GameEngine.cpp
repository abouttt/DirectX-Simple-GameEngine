#include "pch.h"
#include "Component.h"
#include "GameEngine.h"

GameEngine::GameEngine()
	: mbInit(false)
	, mInput()
	, mTime()
	, mResources()
{
}

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!mInput.init(hInstance, hWnd) ||
		!mRenderer.init(hWnd, width, height, bWindowed) ||
		!mResources.init(mRenderer.mD3DDevice))
	{
		return false;
	}

	mTime.init();

	Component::mGameEnginePtr = this;

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

RenderManager& GameEngine::GetRenderer()
{
	return mRenderer;
}

ResourceManager& GameEngine::GetResources()
{
	return mResources;
}
