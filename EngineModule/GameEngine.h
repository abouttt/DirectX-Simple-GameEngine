#pragma once

#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

//#include "GameObject.h"
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
	TimeManager& GetTime();
	RenderManager& GetRenderer();
	ResourceManager& GetResources();

private:
	void loadResources();

private:
	bool mbInit;
	InputManager mInput;
	RenderManager mRenderer;
	ResourceManager mResources;
	TimeManager mTime;

	std::vector<std::unique_ptr<GameObject>> mScene;
};

