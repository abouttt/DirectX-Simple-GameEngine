#pragma once

#include "Color.h"

class RenderManager
{
public:
	friend class GameEngine;

public:
	RenderManager();
	~RenderManager();

public:
	int GetWidth();
	int GetHeight();
	Color GetBackgroundColor();
	void SetBackgroundColor(const Color& color);

private:
	void preRender();
	void render();
	void drawUI();
	void postRender();

	void updateCamera();

	bool init(const HWND hWnd, const int width, const int height, const bool bWindowed);
	bool initDevice(const HWND hWnd, const bool bWindowed);
	void initPipeline();
	void release();

private:
	bool mbInit;
	int mWidth;
	int mHeight;
	IDirect3DDevice9* mD3DDevice;
	Color mBackgroundColor;
};

