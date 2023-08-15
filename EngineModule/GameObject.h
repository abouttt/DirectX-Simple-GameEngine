#pragma once

#include "TransformComponent.h"

class GameObject
{
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

public: // ÄÄÆ÷³ÍÆ®
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
	bool RemoveComponent(Component* const component);
	template<typename T>
	bool RemoveComponent();

private:
	bool mbActive;
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
			result.emplace_back(t);
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

	auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
	newComponent->mOwnerPtr = this;

	mComponents.emplace_back(std::move(newComponent));

	return static_cast<T*>(mComponents.back().get());
}

template<typename T>
inline bool GameObject::RemoveComponent()
{
	static_assert(std::is_base_of<Component, T>::value);

	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if (dynamic_cast<T*>(it->get()))
		{
			mComponents.erase(it);
			return true;
		}
	}

	return false;
}
