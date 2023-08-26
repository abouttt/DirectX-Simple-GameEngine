#include "pch.h"
#include "EngineUtil.h"
#include "GameEngine.h"
#include "Types.h"
#include "Scene.h"
#include "SoundComponent.h"

GameEngine::GameEngine()
	: mbInit(false)
	, mInput()
	, mRenderer()
	, mResources()
	, mTime()
	, mScenes()
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
		!mResources.init(mRenderer.mD3DDevice) ||
		!SoundComponent::init())
	{
		return false;
	}

	mTime.init();

	Component::mEnginePtr = this;
	Scene::mEnginePtr = this;

	loadResources();

	return true;
}

void GameEngine::Release()
{
	mInput.release();
	mRenderer.release();
}

void GameEngine::OnTick()
{
	if (mScenes.mbReserved)
	{
		mInput.clear();
		mTime.clear();
		mScenes.loadScene();
	}

	// 성능 측정 시작
	mTime.beginTick();

	// Input Event
	mInput.update();

	// Game Logic
	auto scene = mScenes.GetActiveScene();
	scene->update();
	scene->lateUpdate();
	SoundComponent::update();
	
	// Scene Rendering
	mRenderer.preRender();
	mRenderer.render();
	mRenderer.drawUI();
	mRenderer.postRender();

	// Decommissioning
	scene->cleanupGameObjects();

	// 성능 측정 종료
	mTime.endTick();
}

InputManager& GameEngine::GetInput()
{
	return mInput;
}

RenderManager& GameEngine::GetRenderer()
{
	return mRenderer;
}

ResourceManager& GameEngine::GetResources()
{
	return mResources;
}

TimeManager& GameEngine::GetTime()
{
	return mTime;
}

SceneManager& GameEngine::GetScenes()
{
	return mScenes;
}

void GameEngine::loadResources()
{
	// Mesh
	mResources.CreateAndAddNativeMesh(_T("Cube"), engineutil::GetCubeMesh(mRenderer.mD3DDevice));
	mResources.CreateAndAddNativeMesh(_T("Sphere"), engineutil::GetSphereMesh(mRenderer.mD3DDevice));
	mResources.CreateAndAddNativeMesh(_T("Quad"), engineutil::GetQuadMesh(mRenderer.mD3DDevice));

	// Texture
	mResources.LoadTexture(_T("Crate"), _T("Textures/crate.jpg"));
	mResources.LoadTexture(_T("DoomGuy"), _T("Textures/doomguy.png"));
	mResources.LoadTexture(_T("Cacodoom"), _T("Textures/cacodoom.png"));
	mResources.LoadTexture(_T("Fire"), _T("Textures/fire.jpg"));
	mResources.LoadTexture(_T("Ice"), _T("Textures/ice.jpg"));

	// Material
	mResources.CreateAndAddMaterial(_T("Default-Material"), eRenderingMode::Opaque, engineutil::MTRL_WHITE, nullptr);
	mResources.CreateAndAddMaterial(_T("Crate"), eRenderingMode::Opaque, engineutil::MTRL_WHITE, mResources.GetTexture(_T("Crate")));
	mResources.CreateAndAddMaterial(_T("DoomGuy"), eRenderingMode::Cutout, engineutil::MTRL_WHITE, mResources.GetTexture(_T("DoomGuy")));
	mResources.CreateAndAddMaterial(_T("Cacodoom"), eRenderingMode::Cutout, engineutil::MTRL_WHITE, mResources.GetTexture(_T("Cacodoom")));
	mResources.CreateAndAddMaterial(_T("Fire"), eRenderingMode::Opaque, engineutil::MTRL_WHITE, mResources.GetTexture(_T("Fire")));
	mResources.CreateAndAddMaterial(_T("Ice"), eRenderingMode::Opaque, engineutil::MTRL_WHITE, mResources.GetTexture(_T("Ice")));
}
