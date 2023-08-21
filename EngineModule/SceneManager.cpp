#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: mbReserved(false)
	, mScenes()
	, mCurrentSceneIndex(0)
	, mNextSceneIndex(-1)
{
}

SceneManager::~SceneManager()
{
}

std::size_t SceneManager::GetSceneCount()
{
	return mScenes.size();
}

Scene* SceneManager::GetActiveScene()
{
	return mScenes[mCurrentSceneIndex].get();
}

Scene* SceneManager::GetSceneAt(const std::size_t index)
{
	assert(index >= 0 && index < mScenes.size());

	return mScenes[index].get();
}

void SceneManager::LoadScene(const std::size_t index)
{
	assert(!mScenes.empty());
	assert(index >= 0 && index < mScenes.size());

	mNextSceneIndex = index;
	mbReserved = true;
}

void SceneManager::LoadScene(const std::wstring& name)
{
	assert(!mScenes.empty());

	for (std::size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenes[i]->GetName() == name)
		{
			LoadScene(i);
			break;
		}
	}
}

void SceneManager::loadScene()
{
	mScenes[mCurrentSceneIndex]->release();
	mScenes[mNextSceneIndex]->Init();
	mCurrentSceneIndex = mNextSceneIndex;
	mNextSceneIndex = -1;
	mbReserved = false;
}
