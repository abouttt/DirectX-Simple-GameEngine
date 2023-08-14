#include "pch.h"
#include "WindowsPlayer.h"
#include "WindowsUtil.h"
#include "GameEngine.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!wndplayer::InitWindowsApp(hInstance, wndplayer::gWidth, wndplayer::gHeight))
	{
		return 0;
	}

	GameEngine gameEngine;
	gameEngine.Init(hInstance, wndplayer::gWndHandler, wndplayer::gWidth, wndplayer::gHeight, true);

	wndutil::Show(wndplayer::gWndHandler);
	wndutil::SetCenterWindow(wndplayer::gWndHandler);

	static float previousTimer = 0.f;
	static float updatePeriod = 500.f;
	while (wndplayer::Tick())
	{
		gameEngine.OnTick();
	}

	gameEngine.Release();
	wndplayer::Destroy();

	return 0;
}