#include "pch.h"
#include "DXContext.h"

IDirect3DDevice9* DXContext::mD3DDevice = nullptr;

IDirect3DDevice9* DXContext::GetDevice()
{
	return mD3DDevice;
}

bool DXContext::init(const HWND hWnd, const int width, const int height, const bool bWindowed, const D3DDEVTYPE deviceType)
{
	if (mD3DDevice)
	{
		return false;
	}

	IDirect3D9* d3d9;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		::MessageBox(nullptr, _T("DXContext/Direct3DCreate9 : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// �ϵ���� ���ؽ� ���μ����� Ȯ���Ѵ�.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);
	long vp = caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ?
		D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp{};
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 32��Ʈ �ȼ� ����
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = bWindowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hWnd, vp, &d3dpp, &mD3DDevice);
	if (FAILED(hr))
	{
		// 16 ��Ʈ ���� ���۷� �ٽ� �õ��Ѵ�.
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hWnd, vp, &d3dpp, &mD3DDevice);
		if (FAILED(hr))
		{
			::MessageBox(nullptr, _T("DXContext/CreateDevice : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
	}

	d3d9->Release();

	return true;
}

void DXContext::release()
{
	if (mD3DDevice)
	{
		mD3DDevice->Release();
	}
}