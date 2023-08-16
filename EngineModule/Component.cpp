#include "pch.h"
#include "Component.h"
#include "GameObject.h"

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