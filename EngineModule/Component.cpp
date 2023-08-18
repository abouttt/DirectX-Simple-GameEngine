#include "pch.h"

#include "Component.h"
#include "GameEngine.h"
#include "GameObject.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
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

void Component::SetName(const std::wstring& name)
{
	mOwnerPtr->SetName(name);
}

void Component::SetTag(const std::wstring& tag)
{
	mOwnerPtr->SetTag(tag);
}

InputManager& Component::GetInput()
{
	return mEnginePtr->GetInput();
}

RenderManager& Component::GetRenderer()
{
	return mEnginePtr->GetRenderer();
}

ResourceManager& Component::GetResources()
{
	return mEnginePtr->GetResources();
}

TimeManager& Component::GetTime()
{
	return mEnginePtr->GetTime();
}
