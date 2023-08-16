#pragma once

#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"

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

private:
	bool mbInit;
	InputManager mInput;
	TimeManager mTime;
	RenderManager mRenderer;
};

