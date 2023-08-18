#pragma once

class GameEngine;
class GameObject;
class TransformComponent;
class InputManager;
class RenderManager;
class ResourceManager;
class SceneManager;
class TimeManager;
class Scene;

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
	Scene& GetScene();
	InputManager& GetInput();
	RenderManager& GetRenderer();
	SceneManager& GetScenes();
	ResourceManager& GetResources();
	TimeManager& GetTime();

private:
	static GameEngine* mEnginePtr;
	bool mbDestroyed;
	GameObject* mOwnerPtr;
};

