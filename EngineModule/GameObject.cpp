#include "pch.h"
#include "BehaviourComponent.h"
#include "GameObject.h"

std::list<GameObject*> GameObject::mContainerPtr;
std::list<GameObject*> GameObject::mTrueContainerPtr;
std::list<GameObject*> GameObject::mFalseContainerPtr;

GameObject::GameObject()
	: mbActive(true)
	, mName(_T("GameObject"))
	, mTag(_T("UnTagged"))
	, mComponents()
{
	init();
}

GameObject::GameObject(const std::wstring& name)
	: mbActive(true)
	, mName(name)
	, mTag(_T("UnTagged"))
	, mComponents()
{
	init();
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mbActive(true)
	, mName(name)
	, mTag(tag)
	, mComponents()
{
	init();
}

GameObject::~GameObject()
{
	for (auto it = mContainerPtr.begin(); it != mContainerPtr.end();)
	{
		if (*it == this)
		{
			mContainerPtr.erase(it);
			break;
		}
	}
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

	if (bActive)
	{
		inAndOutContainer(mTrueContainerPtr, mFalseContainerPtr);
	}
	else
	{
		inAndOutContainer(mFalseContainerPtr, mTrueContainerPtr);
	}

	for (auto behaviour : GetComponents<BehaviourComponent>())
	{
		if (!behaviour->IsEnabled())
		{
			continue;
		}

		if (bActive)
		{
			behaviour->OnEnable();
		}
		else
		{
			behaviour->OnDisable();
		}
	}

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

void GameObject::init()
{
	mContainerPtr.emplace_back(this);
	AddComponent<TransformComponent>();
}

void GameObject::inAndOutContainer(std::list<GameObject*>& inContaier, std::list<GameObject*>& outContainer)
{
	for (auto it = outContainer.begin(); it != outContainer.end();)
	{
		if (*it == this)
		{
			outContainer.erase(it);
			break;
		}
	}

	inContaier.emplace_back(this);
}
