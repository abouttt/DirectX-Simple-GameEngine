#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: mbActive(true)
	, mName(_T("GameObject"))
	, mTag(_T("UnTagged"))
	, mComponents()
{
}

GameObject::GameObject(const std::wstring& name)
	: mbActive(true)
	, mName(name)
	, mTag(_T("UnTagged"))
	, mComponents()
{
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mbActive(true)
	, mName(name)
	, mTag(tag)
	, mComponents()
{
}

GameObject::~GameObject()
{
}

bool GameObject::IsActive() const
{
	return false;
}

const std::wstring& GameObject::GetName() const
{
	return mName;
}

const std::wstring& GameObject::GetTag() const
{
	return mTag;
}

void GameObject::SetActive(const bool bActive)
{
	mbActive = bActive;
}

void GameObject::SetName(const std::wstring& name)
{
	mName = name;
}

void GameObject::SetTag(const std::wstring& tag)
{
	mTag = tag;
}

bool GameObject::RemoveComponent(Component* const component)
{
	assert(component);

	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if (it->get() == component)
		{
			mComponents.erase(it);
			return true;
		}
	}

	return false;
}
