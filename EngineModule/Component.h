#pragma once

class GameObject;
class TransformComponent;

class Component
{
public:
	friend class GameObject;

public:
	Component();
	virtual ~Component() = default;

public:
	bool IsActive() const;
	const std::wstring& GetName() const;
	const std::wstring& GetTag() const;
	GameObject* GetGameObject();
	TransformComponent* GetTransform();

	void SetName(const std::wstring& name);
	void SetTag(const std::wstring& tag);

private:
	bool mbDestroyed;
	GameObject* mOwnerPtr;
};

