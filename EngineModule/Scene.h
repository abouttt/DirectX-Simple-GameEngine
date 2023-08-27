#pragma once

#include <MathUtil.h>
#include <Vector3.h>
#include <Quaternion.h>
#include <Matrix4x4.h>

#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

#include "GameObject.h"
#include "Types.h"

#include "BehaviourComponent.h"

enum class eLightType;

class Scene
{
public:
	friend class GameEngine;
	friend class SceneManager;

public:
	Scene(const std::wstring& name);
	virtual ~Scene() = default;

public:
	const std::wstring& GetName() const;
	std::size_t GetRootCount() const;
	std::vector<GameObject*> GetRootGameObject() const;

public:
	GameObject* CreateGameObject(const std::wstring& name, const std::wstring& tag = _T("UnTagged"));
	GameObject* CreateCube(const std::wstring& name);
	GameObject* CreateSphere(const std::wstring& name);
	GameObject* CreateQuad(const std::wstring& name);
	GameObject* CreateCamera(const std::wstring& name);
	GameObject* CreateLight(const std::wstring& name, const eLightType lightType);
	GameObject* CreateImage(const std::wstring& name, Texture* const texture = nullptr);
	GameObject* CreateText(const std::wstring& name);

	GameObject* FindGameObject(const std::wstring& name);
	GameObject* FindGameObjectWithTag(const std::wstring& tag);
	template<typename T>
	T* FindComponent();

	void RemoveGameObject(GameObject* const gameObject);

protected:
	InputManager& GetInput();
	RenderManager& GetRenderer();
	ResourceManager& GetResources();
	TimeManager& GetTime();

	virtual void Init() abstract;

private:
	void update();
	void lateUpdate();
	void cleanupGameObjects();
	GameObject* createGameObjectWithMesh(const std::wstring& name, const std::wstring& meshName);
	void release();

private:
	static GameEngine* mEnginePtr;

	std::wstring mName;
	std::vector<std::unique_ptr<GameObject>> mGameObjects;
};

template<typename T>
inline T* Scene::FindComponent()
{
	for (auto& gameObject : GameObject::mTrueContainerPtr)
	{
		if (auto component = gameObject->GetComponent<T>())
		{
			if (component->IsEnabled())
			{
				return component;
			}
		}
	}

	return nullptr;
}
