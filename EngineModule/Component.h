#pragma once

class GameEngine;
class GameObject;
class TransformComponent;
class InputManager;
class RenderManager;
class ResourceManager;
class TimeManager;

class Component
{
public:
	friend class GameEngine;
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

protected:
	InputManager& GetInput();
	RenderManager& GetRenderer();
	ResourceManager& GetResources();
	TimeManager& GetTime();

private:
	static GameEngine* mGameEnginePtr;
	bool mbDestroyed;
	GameObject* mOwnerPtr;
};

