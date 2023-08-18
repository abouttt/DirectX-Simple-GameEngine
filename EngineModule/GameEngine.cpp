#include "pch.h"
#include "EngineUtil.h"
#include "GameEngine.h"
#include "Types.h"

#include "GameObject.h"

#include "Component.h"
#include "CameraComponent.h"
#include "MeshComponent.h"

GameEngine::GameEngine()
	: mbInit(false)
	, mInput()
	, mRenderer()
	, mResources()
	, mTime()
	, mScene()
{
}

GameEngine::~GameEngine()
{
}

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!mInput.init(hInstance, hWnd) ||
		!mRenderer.init(hWnd, width, height, bWindowed) ||
		!mResources.init(mRenderer.mD3DDevice))
	{
		return false;
	}

	mTime.init();

	Component::mGameEnginePtr = this;

	loadResources();

	//////////
	auto camera = std::make_unique<GameObject>();
	camera->GetTransform()->SetPosition(Vector3(0.f, 0.f, -10.f));
	camera->AddComponent<CameraComponent>();
	mScene.emplace_back(std::move(camera));

	auto cube = std::make_unique<GameObject>();
	cube->GetTransform()->SetPosition(Vector3(0.f, 0.f, 0.f));
	cube->AddComponent<MeshComponent>(mResources.GetMesh(_T("Cube")));
	mScene.emplace_back(std::move(cube));
	//////////

	return true;
}

void GameEngine::Release()
{
	mInput.release();
	mRenderer.release();
}

void GameEngine::OnTick()
{
	// 성능 측정 시작
	mTime.beginTick();

	// Input Event
	mInput.update();

	// Game Logic
	
	// Scene Rendering
	mRenderer.preRender();
	mRenderer.render();
	mRenderer.drawUI();
	mRenderer.postRender();

	// Decommissioning
	
	// 성능 측정 종료
	mTime.endTick();
}

InputManager& GameEngine::GetInput()
{
	return mInput;
}

TimeManager& GameEngine::GetTime()
{
	return mTime;
}

RenderManager& GameEngine::GetRenderer()
{
	return mRenderer;
}

ResourceManager& GameEngine::GetResources()
{
	return mResources;
}

void GameEngine::loadResources()
{
	// Mesh
	mResources.CreateAndAddNativeMesh(_T("Cube"), engineutil::GetCubeMesh(mRenderer.mD3DDevice));
	mResources.CreateAndAddNativeMesh(_T("Sphere"), engineutil::GetSphereMesh(mRenderer.mD3DDevice));
	mResources.CreateAndAddNativeMesh(_T("Quad"), engineutil::GetQuadMesh(mRenderer.mD3DDevice));

	// Texture

	// Material
	mResources.CreateAndAddMaterial(_T("Default-Material"), eRenderingMode::Opaque, engineutil::WHITE_MTRL, nullptr);
}
