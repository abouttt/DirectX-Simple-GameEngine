#pragma once

class GameEngine
{
public:
	GameEngine();

public:
	bool Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed);
	void Release();
	void OnTick();

private:
	bool mbInit;
};

