#include "pch.h"

#include <Matrix4x4.h>

#include "RenderManager.h"
#include "Material.h"

#include "CameraComponent.h"
#include "MeshComponent.h"
#include "LightComponent.h"
#include "TransformComponent.h"

RenderManager::RenderManager()
	: mbInit(false)
	, mWidth(0)
	, mHeight(0)
	, mD3DDevice(nullptr)
	, mBackgroundColor(Color::Grey)
	, mAlphaRenderBegin()
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

Color RenderManager::GetBackgroundColor()
{
	return mBackgroundColor;
}

void RenderManager::SetBackgroundColor(const Color& color)
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
		updateLights();
		partitionMeshes();
		sortTransparencyMeshes();
	}

	// 배경 지우기 / 렌더 시작.
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
		// 불투명 렌더링.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		renderMeshes(MeshComponent::mTrueContainerPtr.begin(), mAlphaRenderBegin);

		// 투명 렌더링.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		renderMeshes(mAlphaRenderBegin, MeshComponent::mTrueContainerPtr.end());
	}
}

void RenderManager::drawUI()
{
	// TODO
}

void RenderManager::postRender()
{
	// 렌더 마무리 / 백 버퍼 스왑.
	if (mD3DDevice)
	{
		mD3DDevice->EndScene();
		mD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void RenderManager::updateCamera()
{
	auto currentCamera = CameraComponent::GetCurrentCamera();
	auto viewMat = currentCamera->GetViewMatrix().NativeMatrix;
	auto projMat = currentCamera->GetProjectionMatrix(mWidth, mHeight).NativeMatrix;
	mD3DDevice->SetTransform(D3DTS_VIEW, &viewMat);
	mD3DDevice->SetTransform(D3DTS_PROJECTION, &projMat);
}

void RenderManager::updateLights()
{
	// 활성화
	for (auto it = LightComponent::mTrueContainerPtr.begin(); it != LightComponent::mTrueContainerPtr.end(); ++it)
	{
		auto light = *it;
		light->updatePositionAndDirection();
		mD3DDevice->SetLight(light->mIndex, &light->mNativeLight);
		mD3DDevice->LightEnable(light->mIndex, true);
	}

	// 비활성화
	for (auto it = LightComponent::mFalseContainerPtr.begin(); it != LightComponent::mFalseContainerPtr.end(); ++it)
	{
		mD3DDevice->LightEnable((*it)->mIndex, false);
	}
}

void RenderManager::partitionMeshes()
{
	// 투명, 불투명 나누기.
	mAlphaRenderBegin = std::partition(MeshComponent::mTrueContainerPtr.begin(), MeshComponent::mTrueContainerPtr.end(),
		[&](MeshComponent* meshComponent)
		{
			return meshComponent->GetMaterial()->GetRenderingMode() == eRenderingMode::Opaque;
		});
}

// 카메라와의 거리에 따라 정렬.
void RenderManager::sortTransparencyMeshes()
{
	auto camPos = CameraComponent::GetCurrentCamera()->GetTransform()->GetPosition();
	Vector3 gapA{};
	Vector3 gapB{};
	MeshComponent::mTrueContainerPtr.sort(
		[&camPos, &gapA, &gapB](MeshComponent* a, MeshComponent* b)
		{
			if (a->GetMaterial()->GetRenderingMode() == eRenderingMode::Opaque)
			{
				return false;
			}

			gapA = camPos - a->GetTransform()->GetPosition();
			gapB = camPos - b->GetTransform()->GetPosition();
			return gapA.GetSizeSq() > gapB.GetSizeSq();
		});
}

void RenderManager::renderMeshes(std::list<MeshComponent*>::iterator begin, std::list<MeshComponent*>::iterator end)
{
	for (auto& it = begin; it != end; ++it)
	{
		(*it)->render(mD3DDevice);
	}
}

bool RenderManager::initDevice(const HWND hWnd, const bool bWindowed)
{
	IDirect3D9* d3d9;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		::MessageBox(nullptr, _T("RenderEngine - initDevice()/Direct3DCreate9() : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 하드웨어 버텍스 프로세싱을 확인한다.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	long vp = caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp{};
	d3dpp.BackBufferWidth = mWidth;
	d3dpp.BackBufferHeight = mHeight;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 32비트 픽셀 포맷
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
		// 16 비트 깊이 버퍼로 다시 시도한다.
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &mD3DDevice);
		if (FAILED(hr))
		{
			::MessageBox(nullptr, _T("RenderEngine - initDevice()/CreateDevice() : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
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
		// 기본.
		mD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		mD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		mD3DDevice->SetRenderState(D3DRS_ZENABLE, true);
		mD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

		// 라이트.
		mD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		mD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, false);	// 정반사광.	
		mD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);	// 법선 정리.

		// 텍스처.
		mD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		mD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		mD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

		mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		// 밉맵.
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
