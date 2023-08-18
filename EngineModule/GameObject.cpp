#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: mbActive(true)
	, mName(_T("GameObject"))
	, mTag(_T("UnTagged"))
	, mComponents()
{
	AddComponent<TransformComponent>();
	SetName(_T("GameObject"));
}

GameObject::GameObject(const std::wstring& name)
	: mbActive(true)
	, mName(name)
	, mTag(_T("UnTagged"))
	, mComponents()
{
	AddComponent<TransformComponent>();
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mbActive(true)
	, mName(name)
	, mTag(tag)
	, mComponents()
{
	AddComponent<TransformComponent>();
}

GameObject::~GameObject()
{
}

bool GameObject::IsActive() const
{
	return mbActive;
}

const std::wstring& GameObject::GetName() const
{
	return mName;
}

const std::wstring& GameObject::GetTag() const
{
	return mTag;
}

TransformComponent* GameObject::GetTransform()
{
	return static_cast<TransformComponent*>(mComponents[0].get());
}

void GameObject::SetActive(const bool bActive)
{
	// 현재 상태와 매개변수 상태가 같다면 진행하지 않는다.
	if (mbActive == bActive)
	{
		return;
	}

	mbActive = bActive;

	auto transform = GetTransform();
	for (std::size_t i = 0; i < transform->GetChildCount(); i++)
	{
		transform->GetChild(i)->GetGameObject()->SetActive(bActive);
	}
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
