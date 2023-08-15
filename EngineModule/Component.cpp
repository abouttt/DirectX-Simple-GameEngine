#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component()
	: mbDestroyed(false)
	, mOwner(nullptr)
{
}

GameObject* Component::GetGameObject()
{
	return mOwner;
}

const std::wstring& Component::GetName() const
{
	return mOwner->GetName();
}

const std::wstring& Component::GetTag() const
{
	return mOwner->GetTag();
}

void Component::SetName(const std::wstring& name)
{
	mOwner->SetName(name);
}

void Component::SetTag(const std::wstring& tag)
{
	mOwner->SetTag(tag);
}
