#pragma once

class GameObject;

class Component
{
public:
	friend class GameObject;

public:
	Component();
	virtual ~Component() = default;

public:
	GameObject* GetGameObject();
	const std::wstring& GetName() const;
	const std::wstring& GetTag() const;
	void SetName(const std::wstring& name);
	void SetTag(const std::wstring& tag);

private:
	bool mbDestroyed;
	GameObject* mOwner;
};

