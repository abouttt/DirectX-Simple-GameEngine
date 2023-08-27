#include "pch.h"
#include "GameBehaviourComponent.h"
#include "GameObject.h"

std::vector<GameObject*> GameObject::mAllContainerPtr;
std::vector<GameObject*> GameObject::mTrueContainerPtr;
std::vector<GameObject*> GameObject::mFalseContainerPtr;

GameObject::GameObject()
	: mbActive(true)
	, mbDestroyed(false)
	, mbRemovedComponent(false)
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
	if (mbDestroyed)
	{
		return;
	}

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
	assert(component);

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
			mbRemovedComponent = true;
			break;
		}
	}
}

void GameObject::init()
{
	mAllContainerPtr.push_back(this);
	mTrueContainerPtr.push_back(this);
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

	removeThisAllContainer();
}

void GameObject::inAndOutContainer(std::vector<GameObject*>& inContaier, std::vector<GameObject*>& outContainer)
{
	for (auto it = outContainer.begin(); it != outContainer.end(); ++it)
	{
		if (*it == this)
		{
			outContainer.erase(it);
			break;
		}
	}

	inContaier.push_back(this);
}

void GameObject::removeThisAllContainer()
{
	if (mbActive)
	{
		mTrueContainerPtr.erase(std::find(mTrueContainerPtr.begin(), mTrueContainerPtr.end(), this));
	}
	else
	{
		mFalseContainerPtr.erase(std::find(mFalseContainerPtr.begin(), mFalseContainerPtr.end(), this));
	}

	mAllContainerPtr.erase(std::find(mAllContainerPtr.begin(), mAllContainerPtr.end(), this));
}

void GameObject::cleanupComponents()
{
	if (!mbRemovedComponent)
	{
		return;
	}

	auto destroyBegin = std::partition(mComponents.begin(), mComponents.end(),
		[](std::unique_ptr<Component>& gameObject)
		{
			return !gameObject->mbDestroyed;
		});

	for (auto it = destroyBegin; it != mComponents.end(); ++it)
	{
		if (auto gb = dynamic_cast<GameBehaviourComponent*>(it->get()))
		{
			if (gb->IsActive())
			{
				gb->OnDestroy();
			}
		}
	}

	mComponents.erase(destroyBegin, mComponents.end());
	mbRemovedComponent = false;
}
