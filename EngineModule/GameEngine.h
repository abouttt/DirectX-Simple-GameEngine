#pragma once

#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

class GameObject;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

public:
	bool Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed);
	void Release();
	void OnTick();

	InputManager& GetInput();
	RenderManager& GetRenderer();
	ResourceManager& GetResources();
	TimeManager& GetTime();
	SceneManager& GetScenes();

private:
	void loadResources();

private:
	bool mbInit;
	InputManager mInput;
	RenderManager mRenderer;
	ResourceManager mResources;
	TimeManager mTime;
	SceneManager mScenes;
};

