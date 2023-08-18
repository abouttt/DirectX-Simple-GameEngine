#include "pch.h"
#include "BehaviourComponent.h"
#include "GameBehaviourComponent.h"
#include "GameObject.h"

std::list<GameObject*> GameObject::mAllContainerPtr;
std::list<GameObject*> GameObject::mTrueContainerPtr;
std::list<GameObject*> GameObject::mFalseContainerPtr;

GameObject::GameObject()
	: mbActive(true)
	, mbDestroyed(false)
	, mName(_T("GameObject"))
	, mTag(_T("UnTagged"))
	, mComponents()
{
	init();
}

GameObject::GameObject(const std::wstring& name)
	: mbActive(true)
	, mbDestroyed(false)
	, mName(name)
	, mTag(_T("UnTagged"))
	, mComponents()
{
	init();
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mbActive(true)
	, mbDestroyed(false)
	, mName(name)
	, mTag(tag)
	, mComponents()
{
	init();
}

GameObject::~GameObject()
{
	release();
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
	if (IsActive() == bActive)
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

void GameObject::RemoveComponent(Component* const component)
{
	if (component->mbDestroyed)
	{
		return;
	}

	for (auto& c : mComponents)
	{
		if (c.get() == component)
		{
			if (auto behaviour = dynamic_cast<BehaviourComponent*>(component))
			{
				behaviour->SetEnabled(false);
			}

			c->mbDestroyed = true;
			break;
		}
	}
}

void GameObject::init()
{
	mAllContainerPtr.emplace_back(this);
	mTrueContainerPtr.emplace_back(this);
	AddComponent<TransformComponent>();
}

void GameObject::destroy()
{
	for (auto behaviour : GetComponents<BehaviourComponent>())
	{
		behaviour->SetEnabled(false);
	}
	mbDestroyed = true;

	auto transform = GetTransform();
	for (std::size_t i = 0; i < transform->GetChildCount(); i++)
	{
		transform->GetChild(i)->GetGameObject()->destroy();
	}
}

void GameObject::release()
{
	for (auto& gb : GetComponents<GameBehaviourComponent>())
	{
		if (gb->IsActive())
		{
			gb->OnDestroy();
		}
	}

	removeThisInAndOutContainer();

	auto it = std::find(mAllContainerPtr.begin(), mAllContainerPtr.end(), this);
	if (it != mAllContainerPtr.end())
	{
		mAllContainerPtr.erase(it);
	}
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

void GameObject::removeThisInAndOutContainer()
{
	if (mbActive)
	{
		auto it = std::find(mTrueContainerPtr.begin(), mTrueContainerPtr.end(), this);
		if (it != mTrueContainerPtr.end())
		{
			mTrueContainerPtr.erase(it);
		}
	}
	else
	{
		auto it = std::find(mFalseContainerPtr.begin(), mFalseContainerPtr.end(), this);
		if (it != mFalseContainerPtr.end())
		{
			mFalseContainerPtr.erase(it);
		}
	}
}

void GameObject::cleanupComponents()
{
	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if ((*it)->mbDestroyed)
		{
			if (auto gb = dynamic_cast<GameBehaviourComponent*>(it->get()))
			{
				if (gb->IsActive())
				{
					gb->OnDestroy();
				}
			}

			mComponents.erase(it--);
		}
	}
}
