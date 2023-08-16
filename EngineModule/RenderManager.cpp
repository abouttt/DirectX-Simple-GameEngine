#include "pch.h"
#include "CameraComponent.h"
#include "RenderManager.h"

RenderManager::RenderManager()
	: mbInit(false)
	, mWidth(0)
	, mHeight(0)
	, mD3DDevice(nullptr)
	, mBackgroundColor(D3DCOLOR_XRGB(128, 128, 128))
{
}

RenderManager::~RenderManager()
{
	release();
}

int RenderManager::GetWidth()
{
	return mWidth;
}

int RenderManager::GetHeight()
{
	return mHeight;
}

D3DCOLOR RenderManager::GetBackgroundColor()
{
	return mBackgroundColor;
}

void RenderManager::SetBackgroundColor(const D3DCOLOR color)
{
	mBackgroundColor = color;
}

bool RenderManager::init(const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	mWidth = width;
	mHeight = height;

	if (!initDevice(hWnd, bWindowed))
	{
		return false;
	}
	else
	{
		initPipeline();
	}

	mbInit = true;
	return true;
}

void RenderManager::preRender()
{
	if (CameraComponent::GetCurrentCamera())
	{
		updateCamera();
	}

	// ��� ����� / ���� ����.
	if (mD3DDevice)
	{
		mD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, mBackgroundColor, 1.f, 0);
		mD3DDevice->BeginScene();
	}
}

void RenderManager::render()
{
	if (mD3DDevice)
	{
		// ������ ������.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		// TODO

		// ���� ������.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		// TODO
	}
}

void RenderManager::drawUI()
{
	// TODO
}

void RenderManager::postRender()
{
	// ���� ������ / �� ���� ����.
	if (mD3DDevice)
	{
		mD3DDevice->EndScene();
		mD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void RenderManager::updateCamera()
{
	auto currentCamera = CameraComponent::GetCurrentCamera();
	mD3DDevice->SetTransform(D3DTS_VIEW, &currentCamera->GetViewMatrix());
	mD3DDevice->SetTransform(D3DTS_PROJECTION, &currentCamera->GetProjectionMatrix(mWidth, mHeight));
}

bool RenderManager::initDevice(const HWND hWnd, const bool bWindowed)
{
	IDirect3D9* d3d9;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		::MessageBox(nullptr, _T("RenderEngine/initDevice/Direct3DCreate9 : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// �ϵ���� ���ؽ� ���μ����� Ȯ���Ѵ�.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	long vp = caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp{};
	d3dpp.BackBufferWidth = mWidth;
	d3dpp.BackBufferHeight = mHeight;
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

	HRESULT hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &mD3DDevice);
	if (FAILED(hr))
	{
		// 16 ��Ʈ ���� ���۷� �ٽ� �õ��Ѵ�.
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &mD3DDevice);
		if (FAILED(hr))
		{
			::MessageBox(nullptr, _T("RenderEngine/initDevice/CreateDevice : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
	}

	d3d9->Release();

	return true;
}

void RenderManager::initPipeline()
{
	if (mD3DDevice)
	{
		// �⺻.
		mD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		mD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		mD3DDevice->SetRenderState(D3DRS_ZENABLE, true);
		mD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

		// ����Ʈ.
		mD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		mD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, false);	// ���ݻ籤.	
		mD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);	// ���� ����.

		// �ؽ�ó.
		mD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		mD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		mD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

		mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		// �Ӹ�.
		mD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		mD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		mD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

void RenderManager::release()
{
	if (mD3DDevice)
	{
		mD3DDevice->Release();
		mD3DDevice = nullptr;
	}

	mbInit = false;
}