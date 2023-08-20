#include "pch.h"

#include "Component.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Scene.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

GameEngine* Component::mEnginePtr = nullptr;

Component::Component()
	: mbDestroyed(false)
	, mOwnerPtr(nullptr)
{
}

bool Component::IsActive() const
{
	return mOwnerPtr->IsActive();
}

const std::wstring& Component::GetName() const
{
	return mOwnerPtr->GetName();
}

const std::wstring& Component::GetTag() const
{
	return mOwnerPtr->GetTag();
}

GameObject* Component::GetGameObject()
{
	return mOwnerPtr;
}

TransformComponent* Component::GetTransform()
{
	return mOwnerPtr->GetTransform();
}

void Component::SetActive(const bool bActive)
{
	mOwnerPtr->SetActive(bActive);
}

void Component::SetName(const std::wstring& name)
{
	mOwnerPtr->SetName(name);
}

void Component::SetTag(const std::wstring& tag)
{
	mOwnerPtr->SetTag(tag);
}

bool Component::IsDestroyed() const
{
	return mbDestroyed;
}

Scene& Component::GetScene()
{
	return *mEnginePtr->GetScenes().GetActiveScene();
}

InputManager& Component::GetInput()
{
	return mEnginePtr->GetInput();
}

RenderManager& Component::GetRenderer()
{
	return mEnginePtr->GetRenderer();
}

SceneManager& Component::GetScenes()
{
	return mEnginePtr->GetScenes();
}

ResourceManager& Component::GetResources()
{
	return mEnginePtr->GetResources();
}

TimeManager& Component::GetTime()
{
	return mEnginePtr->GetTime();
}
