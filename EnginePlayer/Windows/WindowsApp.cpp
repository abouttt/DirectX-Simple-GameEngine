#include "pch.h"

#include <GameEngine.h>

#include "WindowsPlayer.h"
#include "WindowsUtil.h"

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
	static float updatePeriod = 1000.f;
	while (wndplayer::Tick())
	{
		gameEngine.OnTick();

		float currentTime = gameEngine.GetTime().GetElapsedTime();
		if (currentTime - previousTimer > updatePeriod)
		{
			float fps = gameEngine.GetTime().GetFPS();
			wndplayer::SetWindowsStatTitle(fps);
			previousTimer = currentTime;
		}
	}

	gameEngine.Release();
	wndplayer::Destroy();

	return 0;
}