#pragma once

#include "Component.h"

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

	void SetActive(const bool bActive);
	void SetName(const std::wstring& name);
	void SetTag(const std::wstring& tag);

public: // ÄÄÆ÷³ÍÆ®
	template<typename T>
	T* GetComponent();
	template<typename T>
	std::vector<T*> GetComponents();
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

template<typename T, typename ...Args>
inline T* GameObject::AddComponent(Args && ...args)
{
	static_assert(std::is_base_of<Component, T>::value);

	auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
	newComponent->mOwner = this;

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
