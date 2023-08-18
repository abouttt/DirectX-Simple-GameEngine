#pragma once

#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"

class GameEngine
{
public:
	GameEngine();

public:
	bool Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed);
	void Release();
	void OnTick();

	InputManager& GetInput();
	TimeManager& GetTime();
	RenderManager& GetRenderer();
	ResourceManager& GetResources();

private:
	bool mbInit;
	InputManager mInput;
	TimeManager mTime;
	RenderManager mRenderer;
	ResourceManager mResources;
};

