#include "pch.h"
#include "WindowsPlayer.h"
#include "WindowsUtil.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!wndplayer::InitWindowsApp(hInstance, wndplayer::gWidth, wndplayer::gHeight))
	{
		return 0;
	}

	wndutil::Show(wndplayer::gWndHandler);
	wndutil::SetCenterWindow(wndplayer::gWndHandler);

	static float previousTimer = 0.f;
	static float updatePeriod = 500.f;
	while (wndplayer::Tick())
	{
		
	}

	wndplayer::Destroy();

	return 0;
}