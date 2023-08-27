#pragma once

#include "BehaviourComponent.h"
#include "TransformComponent.h"

class GameObject
{
public:
	friend class Scene;

public:
	GameObject();
	GameObject(const std::wstring& name);
	GameObject(const std::wstring& name, const std::wstring& tag);
	~GameObject();

public:
	bool IsActive() const;
	const std::wstring& GetName() const;
	const std::wstring& GetTag() const;
	TransformComponent* GetTransform();

	void SetActive(const bool bActive);
	void SetName(const std::wstring& name);
	void SetTag(const std::wstring& tag);

public: // 컴포넌트
	template<typename T>
	T* GetComponent();
	template<typename T>
	T* GetComponentInChildren();
	template<typename T>
	T* GetComponentInParent();
	template<typename T>
	std::vector<T*> GetComponents();
	template<typename T>
	std::vector<T*> GetComponentsInChildren();
	template<typename T>
	std::vector<T*> GetComponentsInParent();
	
	template<typename T, typename ...Args>
	T* AddComponent(Args&& ...args);
	void RemoveComponent(Component* const component);
	template<typename T>
	void RemoveComponent();

private:
	void init();
	void destroy();
	void release();
	void inAndOutContainer(std::vector<GameObject*>& inContaier, std::vector<GameObject*>& outContainer);
	void removeThisAllContainer();
	void cleanupComponents();

private:
	static std::vector<GameObject*> mAllContainerPtr;
	static std::vector<GameObject*> mTrueContainerPtr;
	static std::vector<GameObject*> mFalseContainerPtr;

	bool mbActive;
	bool mbDestroyed;
	bool mbRemovedComponent;
	std::wstring mName;
	std::wstring mTag;
	std::vector<std::unique_ptr<Component>> mComponents;
};

template<typename T>
inline T* GameObject::GetComponent()
{
	static_assert(std::is_base_of<Component, T>::value);

	for (auto& component : mComponents)
	{
		if (auto t = dynamic_cast<T*>(component.get()))
		{
			return t;
		}
	}

	return nullptr;
}

template<typename T>
inline T* GameObject::GetComponentInChildren()
{
	static_assert(std::is_base_of<Component, T>::value);

	auto transform = GetTransform();

	for (std::size_t i = 0; i < transform->GetChildCount(); i++)
	{
		auto child = transform->GetChild(i);

		if (!child->IsActive())
		{
			continue;
		}

		if (auto component = transform->GetChild(i)->GetGameObject().GetComponent<T>())
		{
			return component;
		}
	}

	return nullptr;
}

template<typename T>
inline T* GameObject::GetComponentInParent()
{
	static_assert(std::is_base_of<Component, T>::value);

	auto transform = GetTransform();

	if (transform->HasParent())
	{
		return transform->GetParent()->GetGameObject().GetComponent<T>();
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> GameObject::GetComponents()
{
	static_assert(std::is_base_of<Component, T>::value);

	std::vector<T*> result;

	for (auto& component : mComponents)
	{
		if (auto t = dynamic_cast<T*>(component.get()))
		{
			result.push_back(t);
		}
	}

	return result;
}

template<typename T>
inline std::vector<T*> GameObject::GetComponentsInChildren()
{
	static_assert(std::is_base_of<Component, T>::value);

	std::vector<T*> result;
	auto transform = GetTransform();

	for (std::size_t i = 0; i < transform->GetChildCount(); i++)
	{
		auto components = transform->GetChild(i)->GetGameObject().GetComponents<T>();
		if (!components.empty())
		{
			result.insert(components.begin(), components.end());
		}
	}

	return result;
}

template<typename T>
inline std::vector<T*> GameObject::GetComponentsInParent()
{
	static_assert(std::is_base_of<Component, T>::value);

	std::vector<T*> result;
	auto transform = GetTransform();

	if (transform->HasParent())
	{
		result = transform->GetParent()->GetGameObject().GetComponents<T>();
	}

	return result;
}

template<typename T, typename ...Args>
inline T* GameObject::AddComponent(Args && ...args)
{
	static_assert(std::is_base_of<Component, T>::value);

	// Transform Component 1개이상 생성 불가능.
	if (std::is_same<TransformComponent, T>::value)
	{
		if (!mComponents.empty())
		{
			return (T*)GetTransform();
		}
	}

	auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
	newComponent->mOwnerPtr = this;

	// Behaviour Component 생성시 최초 OnEnable 호출.
	if (auto behaviour = dynamic_cast<BehaviourComponent*>(newComponent.get()))
	{
		behaviour->OnEnable();
	}

	mComponents.push_back(std::move(newComponent));

	return static_cast<T*>(mComponents.back().get());
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	static_assert(std::is_base_of<Component, T>::value);

	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if (dynamic_cast<T*>(it->get()))
		{
			if (auto behaviour = dynamic_cast<BehaviourComponent*>(*it))
			{
				behaviour->SetEnabled(false);
			}

			(*it)->mbDestroyed = true;
			break;
		}
	}
}
